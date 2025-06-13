#ifndef _MIT_APP_H
#define _MIT_APP_H
const String mit_app_ver = "MIT_APP : V00.000.001";
/*
#ifndef _ESP8266_WIFI_H
  #define _ESP8266_WIFI_H
  #include <ESP8266WiFi.h>
#endif //_ESP8266_WIFI_H
#ifndef _ESPASYNC_WEB_SERVER_H
  #define _ESPASYNC_WEB_SERVER_H  
  #include <ESPAsyncWebServer.h>
#endif //_ESPASYNC_WEB_SERVER_H
*/
#include "Wifi_functions.h"

WiFiServer MIT_server(80);
/******** .INO file functions *********************************/

//extern void ino_file_functions();

/*************************************************************/
//static int DEBUG = 1;

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String request = "";

 String MIT_INFO_DATA =" Hi MIT APP USER!\n This is JIO_Remote (ESP Board No 2).\nPlease Enter\n For Local -> http://192.168.31.250/update  \n OR \n For Global -> https://remote.rajeshv.in/update \nTo update Firmware.";
 /* Hotspot IP : http://192.168.4.1 */
 String DATA;
 char DATA_1[20];
 int MIT_flag = 0;

void MIT_APP_Setup()
{
  WIFI_Setup();
  MIT_server.begin();
}


void Appliction_MIT_APP_Process()
{


    /*
         if(request.indexOf("") > 0 )  { Serial.println(request); }
    else if(request.indexOf("") > 0 )  { Serial.println(request); }
    */


}

void Common_MIT_APP_Process()
{
  if ( request.indexOf("OTA") > 0 )  
     {
       OTA_flag?OTA_flag = 0:OTA_flag = 1;
   
       EEPROM.write(OTA_addr, OTA_flag);
       EEPROM.commit();
       delay(5000);
       ESP.restart();
    }
    else if  ( request.indexOf("WNQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","WNA ",AP_NameChar.c_str());}
    else if  ( request.indexOf("WPQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","WPA ",WiFiPassword.c_str()); }
    else if  ( request.indexOf("HNQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","HNA ",ssid.c_str()); }
    else if  ( request.indexOf("HPQ") > 0 ) { MIT_flag = 1; Serial.println(request);sprintf(DATA_1, "%s%s","HPA ",password.c_str()); }
    else if  ( request.indexOf("STA") > 0 ) { MIT_flag = 3;Serial.println(request); /*Last_OTA_Status(); */}
    
    else if  ( request.indexOf("WN") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,1); }
    else if  ( request.indexOf("WP") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,2); }
    else if  ( request.indexOf("HN") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,3); }
    else if  ( request.indexOf("HP") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); Wifi_update(request,4); }
    else if  ( request.indexOf("WIFIUPDATE") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request); ReadWifiCredentials(); }
    else if  ( request.indexOf("RST") > 0 ) { MIT_flag = 2;if(DEBUG) Serial.println(request);delay(5000);ESP.restart(); }
    
    else if  ( request == "GET / HTTP/1.1" ) { MIT_flag = 4; Serial.println(request);} // For INFO
    
}

void MIT_Main_code()
{
  // Check if a client has connected
    WiFiClient MIT_client = MIT_server.available();
     if (!MIT_client)  {  goto L;  }
 
    // Read the first line of the request
    request = MIT_client.readStringUntil('\r');
    
    MIT_flag = 0;
    
    Appliction_MIT_APP_Process();
    Common_MIT_APP_Process();


    MIT_client.flush();
   
    MIT_client.print( header );
    //MIT_client.print(" "); // put data to send mobile

    if (MIT_flag == 1)
    {
     MIT_client.print(DATA_1);
     Serial.println(DATA_1);
    }
    else if(MIT_flag == 3)
    {
     MIT_client.print(DATA);
     Serial.println(DATA); 
    }
    else if(MIT_flag == 4)
    {
      MIT_client.print(MIT_INFO_DATA);
     Serial.println(MIT_INFO_DATA);
    }
 
    L:
    delay(5);
    wifi_check_loop(); // every 20 min
}







#endif //_MIT_APP_H
