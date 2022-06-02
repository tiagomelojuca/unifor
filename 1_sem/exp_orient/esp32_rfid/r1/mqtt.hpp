// ----------------------------------------------------------------------------------------------------------
// MQTT
// ----------------------------------------------------------------------------------------------------------

#include <PubSubClient.h>

// ----------------------------------------------------------------------------------------------------------

inline void mqtt_connect(PubSubClient& mqtt_instance, const char* mqtt_id, void (*callback)())
{
  delay(1000);
  while (!mqtt_instance.connected())
  {
    if (mqtt_instance.connect(mqtt_id))
    {
      mqtt_instance.subscribe("card/add");
      mqtt_instance.subscribe("card/id/status");
    }
    else
    {
      callback();
      delay(1000);
    }
  }
}

// ----------------------------------------------------------------------------------------------------------

inline void mqtt_verify(PubSubClient& mqtt_instance, const char* mqtt_id, void (*callback)())
{
  if (!mqtt_instance.connected())
  {
    mqtt_connect(mqtt_instance, mqtt_id, callback);
  }
}

// ----------------------------------------------------------------------------------------------------------

extern String addCardOn;
inline void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  String msg_broker;
  char c;

  if (String(topic) == "cards/add") {
    addCardOn = msg_broker;
  }

  for (int i = 0; i < length; i++)
  {
    c = (char)payload[i];
    msg_broker += c;
  }

  Serial.print("[MQTT] Dados recebidos do broker: ");
  Serial.println(msg_broker);
}

// ----------------------------------------------------------------------------------------------------------

inline void mqtt_setup(PubSubClient& mqtt_instance, const char* broker, int port)
{
  mqtt_instance.setServer(broker, port);
  mqtt_instance.setCallback(mqtt_callback);
}

// ----------------------------------------------------------------------------------------------------------
