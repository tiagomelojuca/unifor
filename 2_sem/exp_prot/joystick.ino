// --------------------------------------------------------------------
// JOYSTICK DIY                                                       |
// --------------------------------------------------------------------

#define _IN_
#define _OUT_

#define LED_EMBEDDED    2
#define LED_YELLOW     13
#define LED_GREEN      15
#define LED_BLUE        4
#define LED_RED        32

#define BTN_RED        14
#define BTN_BLUE       12

#define ANALOG_LEFT_X  26
#define ANALOG_LEFT_Y  27
#define ANALOG_RIGHT_X 25
#define ANALOG_RIGHT_Y 33

bool flagBtnRed  = false;
bool flagBtnBlue = false;

// --------------------------------------------------------------------

enum class Led           { EMBEDDED, YELLOW, GREEN, BLUE, RED };

enum class PushButton    { RED, BLUE };

enum class AnalogPad     { LEFT, RIGHT };
enum class DirectionPad  { LEFT, RIGHT, UP, DOWN };

enum class DebugElements { LEDS, BUTTONS, APADS };

// --------------------------------------------------------------------

void setupLeds()
{
  pinMode(LED_EMBEDDED, OUTPUT);
  pinMode(LED_YELLOW,   OUTPUT);
  pinMode(LED_GREEN,    OUTPUT);
  pinMode(LED_BLUE,     OUTPUT);
  pinMode(LED_RED,      OUTPUT);
}

// --------------------------------------------------------------------

int getPin(Led led)
{
  if (led == Led::YELLOW) {
    return LED_YELLOW;
  } else if (led == Led::GREEN) {
    return LED_GREEN;
  } else if (led == Led::BLUE) {
    return LED_BLUE;
  } else if (led == Led::RED) {
    return LED_RED;
  }

  return LED_EMBEDDED;
}

// --------------------------------------------------------------------

bool isOn(Led led)
{
  return digitalRead(getPin(led)) == HIGH;
}

// --------------------------------------------------------------------

void turnOn(Led led)
{
  digitalWrite(getPin(led), HIGH);
}

// --------------------------------------------------------------------

void turnOff(Led led)
{
  digitalWrite(getPin(led), LOW);
}

// --------------------------------------------------------------------

void setState(Led led, bool state)
{
  state ? turnOn(led) : turnOff(led);
}

// --------------------------------------------------------------------

void toggle(Led led)
{
  digitalWrite(getPin(led), isOn(led) ? LOW : HIGH);
}

// --------------------------------------------------------------------

void blink(Led led)
{
  turnOn(led);
  delay(500);
  turnOff(led);
}

// --------------------------------------------------------------------

void setupButtons()
{
  pinMode(BTN_RED,  INPUT_PULLUP);
  pinMode(BTN_BLUE, INPUT_PULLUP);
}

// --------------------------------------------------------------------

int getPin(PushButton btn)
{
  if (btn == PushButton::RED) {
    return BTN_RED;
  } else if (btn == PushButton::BLUE) {
    return BTN_BLUE;
  }

  return -1;
}

// --------------------------------------------------------------------

bool getFlag(int pin)
{
  if (pin == BTN_RED) {
    return flagBtnRed;
  } else if (pin == BTN_BLUE) {
    return flagBtnBlue;
  }

  return false;
}

// --------------------------------------------------------------------

bool getFlag(PushButton btn)
{
  return getFlag(getPin(btn));
}

// --------------------------------------------------------------------

bool setFlag(int pin, bool newValue)
{
  if (pin == BTN_RED) {
    flagBtnRed = newValue;
  } else if (pin == BTN_BLUE) {
    flagBtnBlue = newValue;
  }
}

// --------------------------------------------------------------------

bool setFlag(PushButton btn, bool newValue)
{
  setFlag(getPin(btn), newValue);
}

// --------------------------------------------------------------------

bool deBounce(int pin, bool state)
{
  bool currentState = digitalRead(pin);

  if (state != currentState) {
    delay(5);
    currentState = digitalRead(pin);
  }

  return currentState;
}

// --------------------------------------------------------------------

bool deBounce(int pin)
{
  return deBounce(pin, getFlag(pin));
}

// --------------------------------------------------------------------

void handleButton(
  int pin,
  void (*handleJustPressed)(),
  void (*handleJustReleased)()
)
{
  if (!deBounce(pin)) {
    if (!getFlag(pin)) {
      handleJustPressed();
    }

    setFlag(pin, true);
  }

  if (getFlag(pin) && deBounce(pin)) {
    handleJustReleased();
    setFlag(pin, false);
  }
}

// --------------------------------------------------------------------

void handleButton(
  PushButton btn,
  void (*handleJustPressed)(),
  void (*handleJustReleased)()
)
{
  handleButton(getPin(btn), handleJustPressed, handleJustReleased);
}

// --------------------------------------------------------------------

void pass()
{
}

// --------------------------------------------------------------------

void readStateButtons()
{
  handleButton(PushButton::RED, pass, pass);
  handleButton(PushButton::BLUE, pass, pass);
}

// --------------------------------------------------------------------

void setupAPads()
{
  pinMode(ANALOG_LEFT_X,  INPUT);
  pinMode(ANALOG_LEFT_Y,  INPUT);
  pinMode(ANALOG_RIGHT_X, INPUT);
  pinMode(ANALOG_RIGHT_Y, INPUT);
}

// --------------------------------------------------------------------

int getPinAxisX(AnalogPad pad)
{
  return pad == AnalogPad::LEFT ? ANALOG_LEFT_X : ANALOG_RIGHT_X;
}

// --------------------------------------------------------------------

int getPinAxisY(AnalogPad pad)
{
  return pad == AnalogPad::LEFT ? ANALOG_LEFT_Y : ANALOG_RIGHT_Y;
}

// --------------------------------------------------------------------

bool isPressing(AnalogPad pad, DirectionPad dir)
{
  const int lower =  700;
  const int upper = 3400;
  
  if (dir == DirectionPad::LEFT) {
    return analogRead(getPinAxisX(pad)) <= lower;
  } else if (dir == DirectionPad::RIGHT) {
    return analogRead(getPinAxisX(pad)) >= upper;
  } else if (dir == DirectionPad::UP) {
    return analogRead(getPinAxisY(pad)) >= upper;
  } else if (dir == DirectionPad::DOWN) {
    return analogRead(getPinAxisY(pad)) <= lower;
  }

  return false;
}

// --------------------------------------------------------------------

void debugPressedRED()   { Serial.println("Pressed RED")  ; }
void debugPressedBLUE()  { Serial.println("Pressed BLUE") ; }
void debugReleasedRED()  { Serial.println("Released RED") ; }
void debugReleasedBLUE() { Serial.println("Released BLUE"); }
void debugHandleRED()  { handleButton(BTN_RED,  debugPressedRED,  debugReleasedRED) ; }
void debugHandleBLUE() { handleButton(BTN_BLUE, debugPressedBLUE, debugReleasedBLUE); }
void debugHandle() { debugHandleRED(); debugHandleBLUE(); }

void debugStatePads()
{
  Serial.println(isPressing(AnalogPad::LEFT, DirectionPad::LEFT)  ? "EE = V" : "EE = F");
  Serial.println(isPressing(AnalogPad::LEFT, DirectionPad::RIGHT) ? "ED = V" : "ED = F");
  Serial.println(isPressing(AnalogPad::LEFT, DirectionPad::UP)    ? "EC = V" : "EC = F");
  Serial.println(isPressing(AnalogPad::LEFT, DirectionPad::DOWN)  ? "EB = V" : "EB = F");

  Serial.println(isPressing(AnalogPad::RIGHT, DirectionPad::LEFT)  ? "DE = V" : "DE = F");
  Serial.println(isPressing(AnalogPad::RIGHT, DirectionPad::RIGHT) ? "DD = V" : "DD = F");
  Serial.println(isPressing(AnalogPad::RIGHT, DirectionPad::UP)    ? "DC = V" : "DC = F");
  Serial.println(isPressing(AnalogPad::RIGHT, DirectionPad::DOWN)  ? "DB = V" : "DB = F");
}

void debugLeds()
{
  blink(Led::YELLOW);
  blink(Led::GREEN);
  blink(Led::BLUE);
  blink(Led::RED);
}

void debug(DebugElements elements)
{
  if (elements == DebugElements::LEDS) {
    debugLeds();
  } else if (elements == DebugElements::BUTTONS) {
    debugHandle();
  } else if (elements == DebugElements::APADS) {
    debugStatePads();
  }
}

// --------------------------------------------------------------------

String serializeAxisX(AnalogPad aPad)
{
  if (isPressing(aPad, DirectionPad::LEFT)) {
    return "-1";
  }
  
  if (isPressing(aPad, DirectionPad::RIGHT)) {
    return "1";
  }

  return "0";
}

// --------------------------------------------------------------------

String serializeAxisY(AnalogPad aPad)
{
  if (isPressing(aPad, DirectionPad::UP)) {
    return "-1";
  }
  
  if (isPressing(aPad, DirectionPad::DOWN)) {
    return "1";
  }

  return "0";
}

// --------------------------------------------------------------------

String serializeButton(PushButton btn)
{
  return getFlag(btn) ? "1" : "0";
}

// --------------------------------------------------------------------

String serializeState()
{
  readStateButtons();
  
  // MESSAGE STRUCT: L_APAD_X;L_APAD_Y;R_APAD_X;R_APAD_Y;R_BTN;B_BTN\n
  // L|R_APAD_X|Y : -1 || 0 || 1
  // R|N_BTN      :  0 || 1
  String message = "";
  message += serializeAxisX(AnalogPad::LEFT);   message += ";";
  message += serializeAxisY(AnalogPad::LEFT);   message += ";";
  message += serializeAxisX(AnalogPad::RIGHT);  message += ";";
  message += serializeAxisY(AnalogPad::RIGHT);  message += ";";
  message += serializeButton(PushButton::RED);  message += ";";
  message += serializeButton(PushButton::BLUE); message += ";";
  message += '\n';

  return message;
}

// --------------------------------------------------------------------

void writeStateToSerial()
{
  Serial.write(serializeState().c_str());
}

// --------------------------------------------------------------------

String readStateFromSerial()
{
  // MESSAGE STRUCT: LED_YELLOW;LED_GREEN;LED_BLUE;LED_RED\n
  // LED_* : 0 || 1
  String message = "";
  
  while (Serial.available()) {
    char c = (char) Serial.read();
    
    if (c == '\n') {
      return message;
    }
    
    message += c;
  }
}

// --------------------------------------------------------------------

void deserializeState(
  String _IN_  message,
  bool&  _OUT_ shouldTurnOnLedYellow,
  bool&  _OUT_ shouldTurnOnLedGreen,
  bool&  _OUT_ shouldTurnOnLedBlue,
  bool&  _OUT_ shouldTurnOnLedRed
)
{
  const char* msg = message.c_str();
  
  shouldTurnOnLedYellow = msg[0] == '0' ? false : true;
                       // msg[1] == ';' (pass)
  shouldTurnOnLedGreen  = msg[2] == '0' ? false : true;
                       // msg[3] == ';' (pass)
  shouldTurnOnLedBlue   = msg[4] == '0' ? false : true;
                       // msg[5] == ';' (pass)
  shouldTurnOnLedRed    = msg[6] == '0' ? false : true;
}

// --------------------------------------------------------------------

void handleLedState()
{
  String msg = readStateFromSerial();
  if (msg == "") {
    return;
  }
  
  bool desiredStateYellow, desiredStateGreen, desiredStateBlue, desiredStateRed;
  deserializeState(msg, desiredStateYellow, desiredStateGreen, desiredStateBlue, desiredStateRed);

  setState(Led::YELLOW, desiredStateYellow);
  setState(Led::GREEN, desiredStateGreen);
  setState(Led::BLUE, desiredStateBlue);
  setState(Led::RED, desiredStateRed);
}

// --------------------------------------------------------------------

void setup() {
  setupLeds();
  setupButtons();
  setupAPads();

  Serial.begin(115200);
}

void loop() {
  handleLedState();
  writeStateToSerial();
}

// --------------------------------------------------------------------
