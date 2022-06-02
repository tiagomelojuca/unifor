/*
   --------------------------------------------------------------------------------------------------------------------
   Example sketch/program showing how to read data from a PICC to serial.
   --------------------------------------------------------------------------------------------------------------------
   This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid

   Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
   Reader on the Arduino SPI interface.

   When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
   then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
   you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
   will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
   when removing the PICC from reading distance too early.

   If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
   So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
   details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
   keep the PICCs at reading distance until complete.

   @license Released into the public domain.

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

   More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
*/

// ----------------------------------------------------------------------------------------------------------

#include <SPI.h>
#include <MFRC522.h>
#include <stdio.h>

#include <WiFi.h>
#include <PubSubClient.h>
#define DEBUG_UART_BAUDRATE        115200

/*
  Defines do MQTT
*/
/* Tópico MQTT para o qual o ESP32 enviará os dados */
#define PUB_DATA_CARD "card/id"

/* Tópico MQTT do qual o ESP32 receberá dados */
#define SUB_RECIEVE_DATA_CARD "card/id/status"

/* Substitua aqui por um identificador único para você.
   Caso seu identificador coincidir com o de alguem no
   mesmo broker MQTT, um dos dois terá a conexão derrubada. */
#define MQTT_ID        "RFID_ESP"
String addCardOn;
/*
  Variáveis globais do Wi-Fi e MQTT
*/
/*  Nome da rede wi-fi que o módulo vai se conectar */
const char* ssid_wifi = "bruno";
/*  WI-FI network password */
const char* password_wifi = "12345678";
/* Objeto para conexão a Internet (Wi-Fi) */
WiFiClient espClient;
/* Endereço do broker MQTT que o módulo deve se conectar */
const char* broker_mqtt = "broker.emqx.io";
/* Porta do broker MQTT que deve ser utilizada (padrão: 1883) */
int broker_port = 1883;
/* Objeto para conexão com broker MQTT */
PubSubClient MQTT(espClient);

/*
  Prototypes
*/
void init_wifi(void);
void init_MQTT(void);
void connect_MQTT(void);
void connect_wifi(void);
void verify_wifi_connection(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
/* Função: inicaliza conexão wi-fi
   Parâmetros: nenhum
   Retorno: nenhum
*/
void init_wifi(void)
{
  delay(10);
  Serial.println("------ WI-FI -----");
  Serial.print("Tentando se conectar a seguinte rede wi-fi: ");
  Serial.println(ssid_wifi);
  Serial.println("Aguarde");
  connect_wifi();
}
/* Função: Configura endereço do broker e porta para conexão com broker MQTT
   Parâmetros: nenhum
   Retorno: nenhum
*/

void init_MQTT(void)
{
  MQTT.setServer(broker_mqtt, broker_port);
  /* Informa que todo dado que chegar do broker pelo tópico definido em MQTT_SUB_TOPIC
     Irá fazer a função mqtt_callback ser chamada (e essa, por sua vez, irá escrever
     os dados recebidos no Serial Monitor */
  MQTT.setCallback(mqtt_callback);
}
/* Função: conecta-se ao broker MQTT (se não há conexão já ativa)
   Parâmetros: nenhum
   Retorno: nenhum
*/
void connect_MQTT(void)
{
  while (!MQTT.connected())
  {
    Serial.print("* Tentando se conectar ao seguinte broker MQTT: ");
    Serial.println(broker_mqtt);

    if (MQTT.connect(MQTT_ID))
    {
      Serial.println("Conexao ao broker MQTT feita com sucesso!");
      /* Após conexão, se subescreve no tópico definido por MQTT_SUB_TOPIC.
         Dessa forma, torna possível receber informações do broker por
         este tópico. */
      MQTT.subscribe(SUB_RECIEVE_DATA_CARD);
      MQTT.subscribe("card/add");
    }
    else
    {
      Serial.println("Falha ao se conectar ao broker MQTT.");
      Serial.println("Nova tentativa em 2s...");
      delay(2000);
    }
  }
}
/* Função: connect to wifi network
   Parâmetros: nenhum
   Retorno: nenhum
*/
void connect_wifi(void)
{
  /* If module is already connected to a WI-FI, there is nothing to do here.
     If there isn't WI-FI connection established, a WI-FI connection is done */
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(ssid_wifi, password_wifi);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Successfully connected to WI-FI network: ");
  Serial.println(ssid_wifi);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
/* Função: verifica se há conexão wi-fi ativa (e conecta-se caso não haja)
   Parâmetros: nenhum
   Retorno: nenhum
*/
void verify_wifi_connection(void)
{
  connect_wifi();
}
/*Função: função de callback
          esta função é chamada toda vez que chegam dados
          pelo tópico definido em MQTT_SUB_TOPIC
  Parâmetros: nenhum
  Retorno: nenhum
*/
void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  String msg_broker;
  char c;

  if (String(topic) == "cards/add") {
    addCardOn = msg_broker;
  }

  /* Obtem a string do payload (dados) recebido */
  for (int i = 0; i < length; i++)
  {
    c = (char)payload[i];
    msg_broker += c;
  }
  Serial.print("[MQTT] Dados recebidos do broker: ");
  Serial.println(msg_broker);
}

// ----------------------------------------------------------------------------------------------------------
// VETOR PRIMITIVO
// ----------------------------------------------------------------------------------------------------------

#define MAX_CARDS_NUM   6 // sao apenas 6 cartoes (C nao tem vetor, pro vetor crescer precisaria de malloc)
#define SENTINEL_VALUE 0U // acho que nenhum cartao tem UID == 0
#define INVALID_INDEX  -1 // sinaliza falha nos procedimentos de manipulacao do array (error handling)
#define FOR_EACH_CARD(i) for(int i = 0; i < MAX_CARDS_NUM; i++) // syntax sugar pra mim, mesmo

int cards_push(unsigned int* arr, unsigned int elem)
{
  FOR_EACH_CARD(i)
  {
    if (arr[i] == SENTINEL_VALUE)
    {
      arr[i] = elem;
      return i;
    }

    if (arr[i] == elem)
    {
      return i;
    }
  }

  return INVALID_INDEX;
}

int cards_search(unsigned int* arr, unsigned int elem)
{
  FOR_EACH_CARD(i)
  {
    if (arr[i] == elem)
    {
      return i;
    }
  }

  return INVALID_INDEX;
}

int cards_detach(unsigned int* arr, unsigned int elem)
{
  const int foundId = cards_search(arr, elem);
  if (foundId == INVALID_INDEX)
  {
    return INVALID_INDEX;
  }

  const int lastId = MAX_CARDS_NUM - 1;
  if (foundId == lastId)
  {
    arr[foundId] = SENTINEL_VALUE;
    return foundId;
  }

  for (int i = foundId; i < MAX_CARDS_NUM - 1; i++)
  {
    const unsigned int next = arr[i + 1];
    const bool hasNext = next != 0;
    if (!hasNext)
    {
      return foundId;
    }

    arr[i] = next;
    arr[i + 1] = SENTINEL_VALUE;
  }

  return INVALID_INDEX;
}

void cards_initialize(unsigned int* arr)
{
  FOR_EACH_CARD(i) arr[i] = SENTINEL_VALUE;
}

// ----------------------------------------------------------------------------------------------------------
// RFID
// ----------------------------------------------------------------------------------------------------------

enum RFID_PINS
{
  RST_PIN = 22,
  SS_PIN  =  5
};

void rfid_setup(MFRC522* instance)
{
  SPI.begin();
  instance->PCD_Init();
  delay(4);
  instance->PCD_DumpVersionToSerial();
}

bool rfid_is_idle(MFRC522* instance)
{
  if (!instance->PICC_IsNewCardPresent())
  {
    return true;
  }

  if (!instance->PICC_ReadCardSerial())
  {
    return true;
  }

  return false;
}

unsigned int rfid_read(MFRC522* instance)
{
  // Dump debug info about the card; PICC_HaltA() is automatically called
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  unsigned int card = 0;

  card =  instance->uid.uidByte[0] << 24;
  card += instance->uid.uidByte[1] << 16;
  card += instance->uid.uidByte[2] << 8;
  card += instance->uid.uidByte[3];

  return card;
}

// ----------------------------------------------------------------------------------------------------------
// LED CONTROL
// ----------------------------------------------------------------------------------------------------------

#define DELAY_IN_MS 200

enum LED_PINS
{
  LED_RED   = 12,
  LED_GREEN = 13
};

void leds_setup()
{
  pinMode(LED_RED,   OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void leds_blink(int led)
{
  digitalWrite(led, HIGH);
  delay(DELAY_IN_MS);
  digitalWrite(led, LOW);
}

// ----------------------------------------------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------------------------------------------

MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned int cards[MAX_CARDS_NUM];

void setup() {
  /* Configuração da serial (usada para debug no Serial Monitor */
  Serial.begin(DEBUG_UART_BAUDRATE);
  /* Inicializa conexão wi-fi */
  init_wifi();
  /* inicializa conexão MQTT */
  init_MQTT();
  connect_MQTT();
  while (!Serial);

  leds_setup();
  rfid_setup(&mfrc522);

  cards_initialize(cards);
  cards_push(cards, 1934270220);
  cards_push(cards, 3386475443);
}

void loop() {
  /* Verifica se a conexão wi-fi está ativa e, em caso negativo, reconecta-se ao roteador */
  verify_wifi_connection();
  /* Verifica se a conexão ao broker MQTT está ativa e, em caso negativo, reconecta-se ao broker */
  connect_MQTT();
  MQTT.publish("card/id", "Liberado : 1934270220");

  delay(2000);

  //if(addCardon == "Ativar"){
  //  cards_push(cards, rfid_read(MFRC522* instance);
  //} else {
    //resto do código
  //}
  
  if (rfid_is_idle(&mfrc522))
  {
    return;
  }

  leds_blink(cards_search(cards, rfid_read(&mfrc522)) != -1 ? LED_GREEN : LED_RED);

  mfrc522.PICC_HaltA();
  MQTT.loop();
  delay(200);
}

// ----------------------------------------------------------------------------------------------------------
