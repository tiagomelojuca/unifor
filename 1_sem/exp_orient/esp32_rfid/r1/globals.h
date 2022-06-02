// ----------------------------------------------------------------------------------------------------------
// GLOBALS
// ----------------------------------------------------------------------------------------------------------

#include "cards_vector.hpp"
#include "rfid.hpp"
#include "leds.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"

// ----------------------------------------------------------------------------------------------------------

#define declare_mfrc(instance) MFRC522 instance(SS_PIN, RST_PIN);
#define declare_cvec(instance) unsigned int cards[MAX_CARDS_NUM];
#define declare_mqtt(instance) WiFiClient espClient; PubSubClient instance(espClient);
#define declare_wifi()         const char* g_ssid; const char* g_passwd;
#define declare_stra()         String addCardOn;

// ----------------------------------------------------------------------------------------------------------
