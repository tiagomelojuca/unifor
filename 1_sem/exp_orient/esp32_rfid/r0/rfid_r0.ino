/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */

// ----------------------------------------------------------------------------------------------------------

#include <SPI.h>
#include <MFRC522.h>

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
  Serial.begin(9600);
  while (!Serial);

  leds_setup();
  rfid_setup(&mfrc522);
  
  cards_initialize(cards);
  cards_push(cards, 1934270220);
  cards_push(cards, 3386475443);
}

void loop() {
  if (rfid_is_idle(&mfrc522))
  {
    return;
  }

  leds_blink(cards_search(cards, rfid_read(&mfrc522)) != -1 ? LED_GREEN : LED_RED);

  mfrc522.PICC_HaltA();
}

// ----------------------------------------------------------------------------------------------------------
