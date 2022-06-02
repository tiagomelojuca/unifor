#include "globals.h"

// ----------------------------------------------------------------------------------------------------------

declare_mfrc(mfrc522);
declare_cvec(cards);
declare_mqtt(mqtt);
declare_wifi();
declare_stra();

// ----------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);

  cards_initialize(cards);
  cards_push(cards, 1934270220);
  cards_push(cards, 3386475443);

  rfid_setup(&mfrc522);

  leds_setup();

  wifi_setup("Galaxy A2227AB", "quesenha");
  mqtt_setup(mqtt, "broker.emqx.io", 1883);
}

// ----------------------------------------------------------------------------------------------------------

void loop() { 
  wifi_verify(blink_red_led);
  mqtt_verify(mqtt, "352c93e8-efa3-45e5-872c-8958d969ac0e", blink_red_led);

  skip_if_idle(mfrc522);

  const int card_index = cards_search(cards, rfid_read(&mfrc522));
  leds_blink(card_index != -1 ? LED_GREEN : LED_RED);
  if (card_index != -1)
  {
    String msg = "ACESSO LIBERADO : ";
    msg += cards[card_index];
    mqtt.publish("card/id", msg.c_str());
  }
  
  mfrc522.PICC_HaltA();
}

// ----------------------------------------------------------------------------------------------------------
