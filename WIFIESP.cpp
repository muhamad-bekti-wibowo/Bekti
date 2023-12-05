#include "WIFIESP.h"
WIFIESP::WIFIESP(const char *ssid, const char *pass)
{
  _ssid = ssid;
  _pass = pass;
 
}

void WIFIESP::connecting(int loop)
{
   Serial.print("Connecting To ");
  Serial.println(_ssid);
  WiFi.begin(_ssid);
  int status = WiFi.status();
  while (status != WL_CONNECTED)
  {
    delay(50);
    if (millis() - Millis >= 1000)
    {
      loop--;
      if (loop == 0)
      {
        ESP.restart();
      }
      status = WiFi.status();
      Serial.println(status);
      Millis = millis();
    }
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}