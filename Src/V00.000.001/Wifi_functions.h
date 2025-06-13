#ifndef _WIFI_FUNCTIONS_H
#define _WIFI_FUNCTIONS_H

#include "WIFI_CONFIG.h"

#ifndef _WIFI_CONFIG_H

   String  AP_NameChar = "JioRemote" ;
   String WiFiPassword = "123456789";

   String     ssid = "RajeshJioFiber";
   String password = "Rajesh@1998";
#endif

int Static_IP();
void WIFI_Setup();

static int WIFI_Status = 0;

String Wifi_Pass, Wifi_Name, Hotspot_Name, Hotspot_Pass;

const long interval_WIFI = 1200000; //6000 * 10 =60000 60sec or 1 min * 20 = 1200000  20 min it will check wifi connection
unsigned long previousMillis_WIFI = 0, currentMillis_WIFI = 0; 


int OTA_flag , OTA_addr = 104, Wifi_Name_addr = 350, Wifi_Pass_addr = 370, Hotspot_Name_addr = 390, Hotspot_Pass_addr = 410;


void No_Static_IP()
{
  WiFi.config(0, 0, 0);
}


#ifdef _WIFI_CONFIG_H

int Static_IP()
{
  int ok = 0; //Not Done

    //Set new hostname
  WiFi.hostname(BOARD_NAME.c_str());

  //Get Current Hostname
  Serial.printf("New hostname: %s\n", WiFi.hostname().c_str());

  // Set your Static IP address
  //IPAddress local_IP(192, 168, 31, 250);
  IPAddress local_IP;
  local_IP.fromString(STATIC_IP);
  // Set your Gateway IP address
  //IPAddress gateway(192, 168, 31, 1);
  IPAddress gateway;
  gateway.fromString(GATEWAY_IP);

  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4); //optional

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
      Serial.println("STA Failed to configure");
      ok = 0;
      No_Static_IP();
  }

  return ok ;
}

#else //_WIFI_CONFIG_H

int Static_IP()
{
  int ok = 1; //Done
  // Set your Static IP address
  IPAddress local_IP(192, 168, 31, 250);
  // Set your Gateway IP address
  IPAddress gateway(192, 168, 31, 1);

  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4); //optional

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
      Serial.println("STA Failed to configure");
      ok = 0;
      No_Static_IP();
  }

  return ok ;
}


#endif //_WIFI_CONFIG_H



int writeStringToEEPROM(int addrOffset, String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);

  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  EEPROM.commit();
  delay(100);
  return addrOffset+ 1 + len;
}

int readStringFromEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];

  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)

  *strToRead = String(data);
  delay(100);
  return addrOffset + 1 +newStrLen;
}


void WriteWifiCredentials()
{
  writeStringToEEPROM(Hotspot_Name_addr, AP_NameChar);  // 19 char reserved for
  writeStringToEEPROM(Hotspot_Pass_addr, WiFiPassword);

  writeStringToEEPROM(Wifi_Name_addr, ssid);  // 19 char reserved for
  writeStringToEEPROM(Wifi_Pass_addr, password);  
}

void ReadWifiCredentials()
{
  readStringFromEEPROM(Hotspot_Name_addr, &AP_NameChar);  // 19 char reserved for 
  readStringFromEEPROM(Hotspot_Pass_addr, &WiFiPassword);

  readStringFromEEPROM(Wifi_Name_addr, &ssid);  // 19 char reserved for 
  readStringFromEEPROM(Wifi_Pass_addr, &password);
}



 int Wifi_Decode(char *T,int op,char e)
 {
  char S[20];
  int c=0,i = 7; // pointing to Data
   memset(S,'\0',20);
  for(;T[i];i++)
 {
  if(T[i] == e){i++; break;}
   S[c] = T[i];
   c++;
 }
   if(op == 1)
    {
      Serial.println(S);
    Wifi_Name = String(S);
    Serial.print("WIFI Name from MIT : ");
    Serial.println(Wifi_Name);
    writeStringToEEPROM(390, Wifi_Name);
    }
   else if (op == 2)
    {
    Wifi_Pass =  String(S);
    Serial.print("WIFI Pass from MIT : ");
    Serial.println(Wifi_Pass);
    writeStringToEEPROM(410, Wifi_Pass);    
    }
   else if (op == 3)
    {
    Hotspot_Name =  String(S);
    Serial.print("Hotspot Name from MIT : ");
    Serial.println(Hotspot_Name);
    writeStringToEEPROM(350, Hotspot_Name);
    }
    else if (op == 4)
    {
    Hotspot_Pass =  String(S);
    Serial.print("Hotspot Pass from MIT : ");
    Serial.println(Hotspot_Pass);
    writeStringToEEPROM(370, Hotspot_Pass);
    } 
 return i;
 }

void Wifi_update(String Name, int op)
{
 int n = Name.length();
 char T2[n+1];
 int i=7; // pointing to Wifi Name

 strcpy(T2 , Name.c_str());
 Serial.println(T2);
 i = Wifi_Decode(T2,op,':'); // 1 for Wifi Name
}


void Connect_WIFI(String ssid , String password , int Re_try_count)
{
   // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

     for(int j = 0 ; j < Re_try_count ; j ++)
     {
       if(WiFi.status() != WL_CONNECTED) 
       {
         delay(500);
         Serial.print(".");
       }
       else
       {
         WIFI_Status = 1;
         // Print local IP address and start web server
         Serial.println("");
         Serial.println("WiFi connected.");
         Serial.println("IP address: ");
         Serial.println(WiFi.localIP());
         break;
       }
     }
}

void Set_Hotspot(String ssid , String password)
{
  // Set device as a Wi-Fi Station
  // WiFi.disconnect();
   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   
   boolean conn = WiFi.softAP(ssid, password);
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
}

void WIFI_Setup()
{
  Static_IP();
  Connect_WIFI( ssid , password , 10 );
  if( WIFI_Status == 1 )
  {
    Serial.println("WIFI Connected Successfully ");
  }
  else
  {
    No_Static_IP();
    Set_Hotspot( AP_NameChar , WiFiPassword );
    Serial.println("HOT_SPOT Created Successfully ");
  }
   
}

void wifi_connectedd()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    WIFI_Status = 1 ;
  }
  else
  {
    WIFI_Status = 0 ;
  }
}

void wifi_check_loop()
{
  currentMillis_WIFI = millis();

  if (currentMillis_WIFI - previousMillis_WIFI >= interval_WIFI) 
  {
    previousMillis_WIFI = currentMillis_WIFI; // every 20 min
    
    wifi_connectedd();
    if( WIFI_Status == 0 ) // wifi not connected
    {
      WIFI_Setup();
    }
   }
}




#endif //_WIFI_FUNCTIONS_H
