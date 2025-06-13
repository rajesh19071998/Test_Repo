/*
  -----------------------
  ElegantOTA - Demo Example
  -----------------------
 
  Skill Level: Beginner
 
  This example provides with a bare minimal app with ElegantOTA functionality.
 
  Github: https://github.com/ayushsharma82/ElegantOTA
  WiKi: https://docs.elegantota.pro
 
  Works with both ESP8266 & ESP32
 
  -------------------------------
 
  Upgrade to ElegantOTA Pro: https://elegantota.pro
 
*/
 #ifndef _OTA_V5_H
 #define _OTA_V5_H
 
#if defined(ESP8266)
  
  #ifndef _ESP8266_WIFI_H
    #define _ESP8266_WIFI_H
    #include <ESP8266WiFi.h>
  #endif //_ESP8266_WIFI_H
  #ifndef _WIFI_CLIENT_H
    #define _WIFI_CLIENT_H 
    #include <WiFiClient.h>
  #endif //_WIFI_CLIENT_H
  #ifndef _ESP8266_WEB_SERVER_H
    #define _ESP8266_WEB_SERVER_H
    #include <ESP8266WebServer.h>
  #endif //_ESP8266_WEB_SERVER_H
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WebServer.h>
#endif
 
#include <ElegantOTA.h>
#include "Wifi_functions.h"

const String ota_v5_ver = "OTA_V5 : V00.000.001";



#if defined(ESP8266)
  ESP8266WebServer OTA_server(80);
#elif defined(ESP32)
  WebServer OTA_server(80);
#endif

 static int DEBUG = 1;

unsigned long ota_progress_millis = 0;

const long interval_OTA = 600000; //6000 * 10 = 60000 60sec or 1 min * 10 = 600000  10 min it willgive control OTA to APPL
unsigned long previousMillis_OTA = 0, currentMillis_OTA = 0; 



void Disable_OTA()
{
    OTA_flag = 0;
    Serial.println("OTA_loop_TIME OUT give control to Application");
    EEPROM.write(OTA_addr, OTA_flag);
    EEPROM.commit();
    delay(5000);
    ESP.restart();
}


void onOTAStart() {
  // Log when OTA has started
  Serial.println("OTA update started!");
  // <Add your own code here>
}

void onOTAProgress(size_t current, size_t final) {
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void onOTAEnd(bool success) {
  // Log when OTA has finished
  if (success) {
    Serial.println("OTA update finished successfully!");
    Disable_OTA();
  } else {
    Serial.println("There was an error during OTA update!");
  }
  // <Add your own code here>
}



void OTA_Setup(void) {
 

  WiFi.mode(WIFI_STA);
  WIFI_Setup();

   OTA_server.on("/", []() {
   OTA_server.send(200, "text/plain", "Hi! This is JIO_Remote (ESP Board No 2).\nPlease Enter\n For Local -> http://192.168.31.250/update  \n OR \n For Global -> https://remote.rajeshv.in/update \nTo update Firmware.");
  });

  ElegantOTA.begin(&OTA_server);    // Start ElegantOTA

  // ElegantOTA callbacks
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  OTA_server.begin();
  Serial.println("HTTP OTA_server started");
}


void OTA_loop()
{
  OTA_server.handleClient();
  ElegantOTA.loop();

  currentMillis_OTA = millis();

  if (currentMillis_OTA - previousMillis_OTA >= interval_OTA) 
  {
    previousMillis_OTA = currentMillis_OTA;

    Disable_OTA();
   
  }
}



#endif //_OTA_V5_H
