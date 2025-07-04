#ifndef _INO_
#define _INO_

#define NEW_IDE
//#define OLD_IDE

#if defined OLD_IDE // Arduino IDE version 1.xx
  #include "OTA_V4.h"
#elif defined NEW_IDE  // Arduino IDE version 2.xx
  #include "OTA_V5.h"
#endif

#include "PIN_CONFIG.h"
/*
#include "Application1.h" 
#include "Application2.h"
*/
#include "MIT_APP.h" //please include at last


const String ino_ver = "INO : V00.000.002";
#if defined OLD_IDE // Arduino IDE version 1.xx
  const String VER[] = {ino_ver, mit_app_ver, ota_v4_ver,  wifi_conf_ver};
#elif defined NEW_IDE  // Arduino IDE version 2.xx
  const String VER[] = {ino_ver, mit_app_ver, ota_v5_ver,  wifi_conf_ver};
#endif





void setup() {
 Serial.begin(115200);
 EEPROM.begin(512); 

 

 delay(5000); // Remove
 Serial.println("**** SW Versions *****");
 for(byte i = 0 ; i < 4 ; i ++)
    Serial.println(VER[i]);
 
  //WriteWifiCredentials();
 
  ReadWifiCredentials(); 
 
  Serial.println(AP_NameChar);
  Serial.println(WiFiPassword);
  Serial.println(ssid);
  Serial.println(password);
 
  OTA_flag = EEPROM.read(OTA_addr);
 
 if(OTA_flag)
  {
  OTA_Setup();
  }
 else
  {
  
    MIT_APP_Setup();

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
  }
  
}



void loop() {
 unsigned long currentMillis = millis();
  
  if(OTA_flag)
  {
    OTA_loop();
  }
  else
  {
   MIT_Main_code();
   
   //Application_loop();
  } 

}



#endif //_INO_
