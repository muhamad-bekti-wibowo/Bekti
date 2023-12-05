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
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClientSecure.h>
#include <WIFIESP.h>
#include "github.h"
#include <Client.h>
class Bekti
{
public:
  Bekti(const char *ssid);
  Bekti(const char *ssid, const char *pass);
  void begin();
  void BektiTime();
  String BektiCert();
  String Bektifingerprint();
  String BektiServerName();
  String server();
  String certificate();
  String fingerprint();
  String GET(String data);
  String POST(String data);
  String read( String uid, String name);
  String write( String uid, String name, String value);
  String readwrite( String uid, String name,  String value);

private:
  const char *_ssid;
  const char *_pass;
  String MyServer_ServerName;
  String MyServer_ServerPath;
  String MyServer_Certificate;
  String MyServer_fingerprint;
  String _token;
  String CHAT_ID;
};

