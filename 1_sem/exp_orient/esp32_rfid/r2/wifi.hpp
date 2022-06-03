// ----------------------------------------------------------------------------------------------------------
// MQTT
// ----------------------------------------------------------------------------------------------------------

#include <WiFi.h>

// ----------------------------------------------------------------------------------------------------------

inline void wifi_setup(const char* ssid, const char* passwd, void (*callback)())
{
    WiFi.begin(ssid, passwd);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      callback();
    }
}

// ----------------------------------------------------------------------------------------------------------