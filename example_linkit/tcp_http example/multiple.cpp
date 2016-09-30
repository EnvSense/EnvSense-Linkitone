 /*
   Ubidots WiFi client

   This sketch reads an analog input and sends this value to Ubidots

   Change the macro WIFI_AP, WIFI_PASSWORD, WIFI_AUTH, URL, TOKEN and VARIABLE_ID accordingly.

   based on the Web Client example created 13 July 2010
   by dlf (Metodo2 srl)
   modified 31 May 2012
   by Tom Igoe
   modified 20 Aug 2014
   by MediaTek Inc.
   modified 2 Sep 2015
   by Ubidots, Inc.

   https://ubidots.com/docs/devices/linkitoneWiFi.html#send-multiple-values-to-ubidots

   */

  #include <LTask.h>
  #include <LWiFi.h>
  #include <LWiFiClient.h>

  #define WIFI_AP "MTK Hackathon"
  #define WIFI_PASSWORD ""
  #define WIFI_AUTH LWIFI_OPEN  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.

  // Ubidots information

  #define URL    "things.ubidots.com"
  #define TOKEN  "Sxxxxxxxxx9m4wX"          // replace with your Ubidots token generated in your profile tab
  #define VARID1 "55fda54a762542789fe3415b"                // create a variable in Ubidots and put its ID here (http://app.ubidots.com/ubi/datasources/)
  #define VARID2 "55fda553762542789fe34166" 
  #define VARID3 "55fda55a76254279041bb2cb"

  void setup()
  {
    LTask.begin();
    LWiFi.begin();
    Serial.begin(9600);

    // keep retrying until connected to AP
    Serial.println("Connecting to AP");
    while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
    {
      delay(1000);
    }
  }

  // I plan to use this function in the future to reconnect to WiFi if the connection drops:
  boolean wifi_status(LWifiStatus ws){
    switch(ws){
      case LWIFI_STATUS_DISABLED:
        return false;
      break;
      case LWIFI_STATUS_DISCONNECTED:
        return false;
      break;
      case LWIFI_STATUS_CONNECTED:
        return true;
      break;
    }
    return false;
  }


  void loop()
  {   
    Serial.println("Connecting to Ubidots...");
    LWiFiClient c;
    while (!c.connect(URL, 80))
    {
      Serial.println("Retrying to connect...");
      delay(100);
    }

    Serial.println("Connected!");

    while(1){
      LWifiStatus ws = LWiFi.status();
      boolean status = wifi_status(ws);
      if(!status){
        Serial.println("Connecting to AP");
        while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
        {
          delay(500);
        }
      }
      String payload = "[{\"variable\":\"" VARID1 "\",\"value\":"+ String(analogRead(A0)) + "},{\"variable\":\"" VARID2 "\",\"value\":" + String(analogRead(A1)) + "},{\"variable\":\"" VARID3 "\",\"value\":" + String(analogRead(A2)) + "}]";
      String le = String(payload.length());

      if(!c.connected()){
        while (!c.connect(URL, 80)){
          delay(100);
        }
        Serial.println("Client reconnected!");
      } 

      // Build HTTP POST request
      c.print(F("POST /api/v1.6/collections/values/?token="));
      c.print(TOKEN);
      c.println(F(" HTTP/1.1"));
      c.println(F("Content-Type: application/json"));
      c.print(F("Content-Length: "));
      c.println(le);
      c.print(F("Host: "));
      c.println(URL);
      c.println(); 
      c.println(payload);  

      int v;
      while(c.available()){  
        v = c.read();
        if(v < 0){
          Serial.println("No response.");
          break;
        }
        //Serial.print((char)v);
      }
      delay(1000);
    }
  }
