// ----------------------------------------------------------------------------------------------------------
// MQTT
// ----------------------------------------------------------------------------------------------------------

#include <WiFi.h>

// ----------------------------------------------------------------------------------------------------------

extern const char* g_ssid;
extern const char* g_passwd;

// ----------------------------------------------------------------------------------------------------------

inline void wifi_setup(const char* ssid, const char* passwd)
{
    g_ssid   = ssid;
    g_passwd = passwd;
}

// ----------------------------------------------------------------------------------------------------------

inline void wifi_connect(void (*callback)())
{
  delay(1000);
  WiFi.begin(g_ssid, g_passwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    callback();
    delay(1000);
  }
}

// ----------------------------------------------------------------------------------------------------------

inline void wifi_verify(void (*callback)())
{
  if (WiFi.status() != WL_CONNECTED)
  {
    wifi_connect(callback);
  }
}

// ----------------------------------------------------------------------------------------------------------