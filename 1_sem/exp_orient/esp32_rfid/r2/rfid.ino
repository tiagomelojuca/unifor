#include "globals.h"

// ----------------------------------------------------------------------------------------------------------

declare_mfrc(mfrc522);
declare_cvec(cards);
declare_serv(servo);
declare_mqtt(mqtt);
declare_stra();

// ----------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  delay(500);

  // Data
  cards_initialize(cards);
  cards_push(cards, 1934270220);
  cards_push(cards, 3386475443);

  // Sensors
  rfid_setup(&mfrc522);
  serv_setup(&servo);
  leds_setup();

  // Connection
  wifi_setup("Galaxy A2227AB", "quesenha", leds_blink);
  mqtt_setup(mqtt, "broker.emqx.io", 1883);
}

// ----------------------------------------------------------------------------------------------------------

void loop() { 
  mqtt_verify(mqtt, "352c93e8-efa3-45e5-872c-8958d969ac0e", leds_blink);

  skip_if_idle(mfrc522);

  const int card_index = cards_search(cards, rfid_read(&mfrc522));
  if (card_index != -1)
  {
    serv_unlock_and_relock(&servo);
    String msg = "ACESSO LIBERADO : ";
    msg += cards[card_index];
    mqtt.publish("card/id", msg.c_str());
  }
  else {
    leds_blink();
    mqtt.publish("card/id", "ACESSO NEGADO");
  }
  
  mfrc522.PICC_HaltA();
}

// ----------------------------------------------------------------------------------------------------------
