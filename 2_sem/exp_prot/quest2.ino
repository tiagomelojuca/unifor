#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

#define PIN_BTN_BLUE   32
#define PIN_BTN_GREEN  26
#define PIN_BTN_YELLOW 25
#define PIN_BTN_RED    33

#define PIN_LED_BLUE   13
#define PIN_LED_GREEN  12
#define PIN_LED_YELLOW 14
#define PIN_LED_RED    27

#define NUMERO_RODADAS  5
int VETOR_LEDS[NUMERO_RODADAS];

bool jogando = false;
int rodadaCorrente = 0;

bool stateBtnBlue   = false;
bool stateBtnGreen  = false;
bool stateBtnYellow = false;
bool stateBtnRed    = false;

int GetPin(int idxLed)
{
  if (idxLed == 0) {
    return PIN_LED_BLUE;
  }

  if (idxLed == 1) {
    return PIN_LED_GREEN;
  }

  if (idxLed == 2) {
    return PIN_LED_YELLOW;
  }

  if (idxLed == 3) {
    return PIN_LED_RED;
  }

  return -1;
}

int GetIndex(int pinLed)
{
  if (pinLed == PIN_LED_BLUE) {
    return 0;
  }

  if (pinLed == PIN_LED_GREEN) {
    return 1;
  }

  if (pinLed == PIN_LED_YELLOW) {
    return 2;
  }

  if (pinLed == PIN_LED_RED) {
    return 3;
  }

  return -1;
}

int GetLedFromBtn(int pinBtn)
{
  if (pinBtn == PIN_BTN_BLUE) {
    return PIN_LED_BLUE;
  }

  if (pinBtn == PIN_BTN_GREEN) {
    return PIN_LED_GREEN;
  }

  if (pinBtn == PIN_BTN_YELLOW) {
    return PIN_LED_YELLOW;
  }

  if (pinBtn == PIN_BTN_RED) {
    return PIN_LED_RED;
  }

  return -1;
}

void atualizaRodada(int _rodada)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(46, 8);
  display.println(F("RODADA:"));

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(58, 28);
  display.print(String(_rodada));

  display.display();
}

void iniciaJogo()
{
  const int timeBetween = 250;
  digitalWrite(PIN_LED_BLUE,    LOW);
  digitalWrite(PIN_LED_GREEN,   LOW);
  digitalWrite(PIN_LED_YELLOW,  LOW);
  digitalWrite(PIN_LED_RED,     LOW);
  delay(1000);
  digitalWrite(PIN_LED_BLUE,   HIGH);
  delay(timeBetween);
  digitalWrite(PIN_LED_BLUE,    LOW);
  digitalWrite(PIN_LED_GREEN,  HIGH);
  delay(timeBetween);
  digitalWrite(PIN_LED_GREEN,   LOW);
  digitalWrite(PIN_LED_YELLOW, HIGH);
  delay(timeBetween);
  digitalWrite(PIN_LED_YELLOW,   LOW);
  digitalWrite(PIN_LED_RED,     HIGH);
  delay(timeBetween);
  digitalWrite(PIN_LED_RED,      LOW);
  delay(timeBetween);
}

void finalizarJogo(const char* msg)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 26);
  display.println(F(msg));

  display.display();

  for (;;) {
    digitalWrite(PIN_LED_BLUE,   HIGH);
    digitalWrite(PIN_LED_GREEN,  HIGH);
    digitalWrite(PIN_LED_YELLOW, HIGH);
    digitalWrite(PIN_LED_RED,    HIGH);
    delay(1000);
    digitalWrite(PIN_LED_BLUE,   LOW);
    digitalWrite(PIN_LED_GREEN,  LOW);
    digitalWrite(PIN_LED_YELLOW, LOW);
    digitalWrite(PIN_LED_RED,    LOW);
    delay(1000);
  }
}

void printaNoDisplay(const char* msg)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 26);
  display.println(F(msg));

  display.display();
}

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  delay(1000);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  pinMode(PIN_LED_BLUE,   OUTPUT);
  pinMode(PIN_LED_GREEN,  OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED,    OUTPUT);
  
  pinMode(PIN_BTN_BLUE,   INPUT_PULLUP);
  pinMode(PIN_BTN_GREEN,  INPUT_PULLUP);
  pinMode(PIN_BTN_YELLOW, INPUT_PULLUP);
  pinMode(PIN_BTN_RED,    INPUT_PULLUP);

  for (int i = 0; i < NUMERO_RODADAS; i++) {
    VETOR_LEDS[i] = random(0, 4);
    Serial.println(VETOR_LEDS[i]);
  }

  iniciaJogo();
  atualizaRodada(1);
  delay(2000);
}

bool checkBtn(int btn)
{
  return digitalRead(btn) == LOW;
}

bool debounce(bool state, int pin)
{
  bool currentState = digitalRead(pin);
  if (currentState != state) {
    delay(7);
    currentState = digitalRead(pin);
  }

  return currentState;
}

void acendeLed(int pin)
{
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);
}

void exibeRodada(int rodada)
{
  for (int i = 0; i < rodada + 1; i++) {
    acendeLed(GetPin(VETOR_LEDS[i]));
  }
  
  jogando = true;
}

bool apertou(bool& state, int pinBtn, int pinLed)
{
  if (!debounce(state, pinBtn)) {
    state = true;
    digitalWrite(pinLed, HIGH);
    return false;
  }

  if (debounce(state, pinBtn) && state) {
    state = false;
    digitalWrite(pinLed, LOW);
    return true;
  }

  return false;
}

bool apertou(int pinBtn)
{
  if (pinBtn == PIN_BTN_BLUE) {
    return apertou(stateBtnBlue, PIN_BTN_BLUE, PIN_LED_BLUE);
  }

  if (pinBtn == PIN_BTN_GREEN) {
    return apertou(stateBtnGreen, PIN_BTN_GREEN, PIN_LED_GREEN);
  }

  if (pinBtn == PIN_BTN_YELLOW) {
    return apertou(stateBtnYellow, PIN_BTN_YELLOW, PIN_LED_YELLOW);
  }

  if (pinBtn == PIN_BTN_RED) {
    return apertou(stateBtnRed, PIN_BTN_RED, PIN_LED_RED);
  }

  return false;
}

int efetuaPolling()
{
  if (apertou(PIN_BTN_BLUE)) {
    return PIN_BTN_BLUE;
  }

  if (apertou(PIN_BTN_GREEN)) {
    return PIN_BTN_GREEN;
  }

  if (apertou(PIN_BTN_YELLOW)) {
    return PIN_BTN_YELLOW;
  }

  if (apertou(PIN_BTN_RED)) {
    return PIN_BTN_RED;
  }

  return 0;
}

void recebeJogada(int rodada)
{
  int palpitesJogada[NUMERO_RODADAS];
  
  for (int i = 0; i < rodada + 1; i++) {
    int palpiteCorrente = 0;
    while (!palpiteCorrente) {
      palpiteCorrente = efetuaPolling();
    }

    if (GetIndex(GetLedFromBtn(palpiteCorrente)) != VETOR_LEDS[i]) {
      rodadaCorrente = -1;
      delay(500);
      break;
    }
  }

  if (rodadaCorrente != -1) {
    rodadaCorrente++;
    if (rodadaCorrente < NUMERO_RODADAS) {
      atualizaRodada(rodadaCorrente + 1);
    }
    
    jogando = false;
    delay(2000);
  }
}

void loop()
{
  if (rodadaCorrente < 0) {
    finalizarJogo("VOCE PERDEU!");
  }

  if (rodadaCorrente == NUMERO_RODADAS) {
    finalizarJogo("VOCE GANHOU!");
  }
  
  if (jogando) {
    recebeJogada(rodadaCorrente);
  } else {
    exibeRodada(rodadaCorrente);
  }
}
