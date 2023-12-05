/*
  06 Agustust 2023 developed by Muhammad Bekti Wibowo

  Program ini dikembangkan oleh Muhammad Bekti Wibowo untuk pengembangan project dengan HTTPS.
  khususnya untuk project saya di https://
  Jika saya masih belum bisa membeli server sendiri. dukung saya untuk membeli server di https://saweria.co/FastProjectMBW

  Program Sebelumnya Dibuat Oleh Rui Santos
  Lengkapi detail proyek di Lengkapi detail proyek di https://RandomNerdTutorials.com/
  Izin dengan ini diberikan, tanpa biaya, kepada siapa pun yang mendapatkan salinan perangkat lunak ini dan file dokumentasi terkait.
  Pemberitahuan hak cipta di atas dan pemberitahuan izin ini harus menyertakan semua salinan atau sebagian besar dari Perangkat Lunak.

  Referensi
  ~ https://randomnerdtutorials.com/esp8266-nodemcu-https-requests/
  ~ https://randomnerdtutorials.com/esp32-https-requests/
  ~ https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/
  ~ https://www.geeksforgeeks.org/http-headers-content-type/
  ~ https://circuits4you.com/2019/02/08/esp8266-nodemcu-https-secured-post-request/

  This program was developed by Muhammad Bekti Wibowo for project development with HTTPS.
  especially for my project at https://
  If I still can't buy my own server. support me to buy server at https://saweria.co/FastProjectMBW

  Previous Program Created By Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/
  Permission is hereby granted, without charge, to anyone who obtains a copy of this software and associated documentation files.
  The above copyright notice and this permission notice must include all copies or a large portion of the Software.

  Reference
  ~ https://randomnerdtutorials.com/esp8266-nodemcu-https-requests/
  ~ https://randomnerdtutorials.com/esp32-https-requests/
  ~ https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/
  ~ https://www.geeksforgeeks.org/http-headers-content-type/
  ~ https://circuits4you.com/2019/02/08/esp8266-nodemcu-https-secured-post-request/
*/

#include "Bekti.h"
WiFiClientSecure client;
WiFiClientSecure clients;

Bekti::Bekti(const char *ssid)
{
  _ssid = ssid;
}
Bekti::Bekti(const char *ssid, const char *pass)
{
  _ssid = ssid;
  _pass = pass;
}
void Bekti::begin()
{
  WIFIESP wifi(_ssid, _pass);
  wifi.connecting(20);
  BektiTime();
  BektiCert();
  Bektifingerprint();
  BektiServerName();
}
void Bekti::BektiTime()
{
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2)
  {
    delay(500);
    now = time(nullptr);
    // Serial.println(now);
  }
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
}
String Bekti::BektiCert()
{
  X509List cert(CERTIFICATE);
  client.setTrustAnchors(&cert);
  HTTPClient https;
  if (https.begin(client, "https://muhamad-bekti-wibowo.github.io/redirects/cert.txt"))
  {
    int httpCode = https.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = https.getString();
        payload.trim();
        https.end();
        // Serial.println(payload);
        MyServer_Certificate = payload;
        return payload;
      }
    }
    else
    {
      https.end();
      return "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
    }
  }
  return "Pengiriman data gagal";
}
String Bekti::Bektifingerprint()
{
  X509List cert(CERTIFICATE);
  client.setTrustAnchors(&cert);
  HTTPClient https;
  if (https.begin(client, "https://muhamad-bekti-wibowo.github.io/redirects/fingerprint.txt"))
  {
    int httpCode = https.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = https.getString();
        payload.trim();
        https.end();
        // Serial.println(payload);
        MyServer_fingerprint = payload;
        return payload;
      }
    }
    else
    {
      https.end();
      return "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
    }
  }
  return "Pengiriman data gagal";
}
String Bekti::BektiServerName()
{
  X509List cert(CERTIFICATE);
  client.setTrustAnchors(&cert);
  HTTPClient https;
  if (https.begin(client, "https://muhamad-bekti-wibowo.github.io/redirects/projects.txt"))
  {
    int httpCode = https.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = https.getString();
        payload.trim();
        https.end();
        // Serial.println(payload);
        MyServer_ServerName = payload;
        return payload;
      }
    }
    else
    {
      https.end();
      return "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
    }
  }
  return "Pengiriman data gagal";
}
String Bekti::server()
{
  return MyServer_ServerName;
}
String Bekti::certificate()
{
  return MyServer_Certificate;
}
String Bekti::fingerprint()
{
  return MyServer_fingerprint;
}
String Bekti::GET(String data)
{
  X509List cert(MyServer_Certificate.c_str());
  client.setTrustAnchors(&cert);
  HTTPClient https;
  Serial.println("https://" + MyServer_ServerName + "/" + data);
  if (https.begin(client, "https://" + MyServer_ServerName + "/" + data))
  {
    int httpCode = https.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = https.getString();
        payload.trim();
        https.end();
        // Serial.println(payload);
        return payload;
      }
    }
    else
    {
      https.end();
      return "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
    }
  }
  return "Pengiriman data gagal";
}
String Bekti::POST(String data)
{
  X509List cert(MyServer_Certificate.c_str());
  client.setTrustAnchors(&cert);
  if (client.connect(MyServer_ServerName.c_str(), 443))
  {
    client.print(String("POST ") + "/api.php" + " HTTP/1.1\r\n" +
                 "Host: " + MyServer_ServerName.c_str() + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                 "Content-Length: " + "" + String(data.length()).c_str() + "" + "\r\n\r\n" +
                 "" + data.c_str() + "\r\n\r\n" +
                 "Connection: close\r\n\r\n");
    client.readStringUntil('H');
    String Reply = "H";
    while (client.available())
    {
      char c = client.read();
      Reply += String(c);
    }
    client.stop();
    Reply = (Reply.substring(Reply.indexOf("\r\n\r\n"), Reply.indexOf("\n\n\n")));
    Reply.trim();
    return Reply;
  }
  return "";
}
String Bekti::read(String uid, String name)
{
  X509List cert(MyServer_Certificate.c_str());
  client.setTrustAnchors(&cert);
  if (client.connect(MyServer_ServerName.c_str(), 443))
  {
    String data = "C45EC0616164A18CAC44C5512FC7CF93=" + String(uid + "~" + name + "~read");
    client.print(String("POST ") + "/api.php" + " HTTP/1.1\r\n" +
                 "Host: " + MyServer_ServerName.c_str() + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                 "Content-Length: " + "" + String(data.length()).c_str() + "" + "\r\n\r\n" +
                 "" + data.c_str() + "\r\n\r\n" +
                 "Connection: close\r\n\r\n");
    String Reply = "H";
    while (client.available())
    {
      char c = client.read();
      Reply += String(c);
    }
    client.stop();
    Reply = (Reply.substring(Reply.indexOf("\r\n\r\n"), Reply.indexOf("\n\n\n")));
    Reply.trim();
    return Reply;
  }
  return "";
}
String Bekti::write(String uid, String name, String value)
{
  X509List cert(MyServer_Certificate.c_str());
  client.setTrustAnchors(&cert);
  if (client.connect(MyServer_ServerName.c_str(), 443))
  {
    String data = "C45EC0616164A18CAC44C5512FC7CF93=" + String(uid + "~" + name + "~write~" + value);
    client.print(String("POST ") + "/api.php" + " HTTP/1.1\r\n" +
                 "Host: " + MyServer_ServerName.c_str() + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                 "Content-Length: " + "" + String(data.length()).c_str() + "" + "\r\n\r\n" +
                 "" + data.c_str() + "\r\n\r\n" +
                 "Connection: close\r\n\r\n");

    client.stop();
    return "true";
  }
  return "false";
}
String Bekti::readwrite(String uid, String name, String value)
{
  X509List cert(MyServer_Certificate.c_str());
  client.setTrustAnchors(&cert);
  if (client.connect(MyServer_ServerName.c_str(), 443))
  {
    String data = "C45EC0616164A18CAC44C5512FC7CF93=" + String(uid + "~" + name + "~readwrite~" + value);
    client.print(String("POST ") + "/api.php" + " HTTP/1.1\r\n" +
                 "Host: " + MyServer_ServerName.c_str() + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                 "Content-Length: " + "" + String(data.length()).c_str() + "" + "\r\n\r\n" +
                 "" + data.c_str() + "\r\n\r\n" +
                 "Connection: close\r\n\r\n");
    client.readStringUntil('H');
    String Reply = "H";
    while (client.available())
    {
      char c = client.read();
      Reply += String(c);
    }
    client.stop();
    Reply = (Reply.substring(Reply.indexOf("\r\n\r\n"), Reply.indexOf("\n\n\n")));
    Reply.trim();
    return Reply;
  }
  return "";
}