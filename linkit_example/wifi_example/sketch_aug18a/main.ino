
#include <cmath>
#include "LDHT.h"
#include <LWiFi.h>
#include <LWiFiClient.h>

// Deployment Info

#define WIFI_AP "LOGOSLAB-slowbro"
#define WIFI_PASSWORD "logoslab"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SITE_URL "mashroom-experiments.tk"

LWiFiClient c;

//
/* Sensor Setup */
//

// Soil Moisture YL-69
uint32_t analogPinSM = A0; // Read soil moisture sensor value

// DHT11 Air Temperature and Humidity
# define DHT_TYPE DHT11

// Used Pin List
uint8_t digitalPin = 8;
LDHT dht( digitalPin, DHT_TYPE );

// Light sensor
uint32_t analogPinLight = A1;

/* Sensor Function Declaration */
int smRead(int pin);
int lightRead(int pin);
float airRead( LDHT dht, int type );
float previousMois = 0.0; // Buffer prevous value to validate integrity
float previousTemp = 0.0; //

/* End of Sensor Function & Setup */

//
/* Internet Function Declaration */
//

// Wifi-base
void initWifi();
void printResponse();
void sendData();
boolean disconnectedMsg = false;

// GPRS-base
void intiGPRS();

void setup()
{
  Serial.begin(115200);

  initWifi();
  /* Sensor Initialization */
  /* Air Temp & Moisture*/
  dht.begin();

}


void loop()
{
//  smRead( analogPinSM );
//  lightRead( analogPinLight );
//  airRead( dht, 0 );
//  delay(2000);
//  airRead( dht, 1 );
//  delay(2000);

  sendData();
  printRespone();

  if (!disconnectedMsg)
  {
    Serial.println("disconnected by server");
    disconnectedMsg = true;
  }
}
void intiGPRS(){
    Serial.println("Attach to GPRS network by auto-detect APN setting");
    while (!LGPRS.attachGPRS())
    {
      delay(500);
    }

    // if you get a connection, report back via serial:
    Serial.print("Connect to ");
    Serial.println(server);
    if (client.connect(server, port))
    {
      Serial.println("connected");
      // Make a HTTP request:
      client.print("GET ");
      client.print(path);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(server);
      client.println("Connection: close");
      client.println();
    }
    else
    {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
}
void initWifi()
{
    int APTryCnt = 60;  // 1 mins
    int ServerTryCnt = 60; // 1 mins
    LWiFi.begin();

    //  keep retrying until connected to AP
    Serial.println("Connecting to AP");
    while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
    {
      delay(1000);
    }

    // keep retrying until connected to website
    Serial.println("Connecting to Server");
    while (0 == c.connect(SITE_URL, 80))
    {
      Serial.println("Re-Connecting to WebSite");
      delay(1000);
    }

//    // send HTTP request, ends with 2 CR/LF
//    Serial.println("send HTTP GET request");
//    c.println("POST / HTTP/1.1");
//    c.println("Host: " SITE_URL);
//    c.println("Connection: close");
//    c.println();
//
//    // waiting for server response
//    Serial.println("waiting HTTP response:");
//    while (!c.available())
//    {
//      delay(100);
//    }
}
void sendData(){
//      String payload = "[{\"variable\":\"" VARID1 "\",\"value\":"+ String(analogRead(A0)) + "},{\"variable\":\"" VARID2 "\",\"value\":" + String(analogRead(A1)) + "},{\"variable\":\"" VARID3 "\",\"value\":" + String(analogRead(A2)) + "}]";
      delay( 2000 );
      float temp = airRead( dht, 0 );
      delay( 2000 );
      float mois = airRead( dht, 1 );

      String payload = "soilMois="+String( smRead( analogPinSM ) )+"&light="+String( lightRead( analogPinLight ) ) +"&air_mois="+String( mois )+"&air_temp="+String( temp )+"&box_id=1";
      String le = String(payload.length());

      if(!c.connected()){
        while (!c.connect( SITE_URL, 80 )){
          delay( 100 );
        }
        Serial.println("Client reconnected!");
      }

      // Build HTTP POST request

      c.println( "POST /index.php HTTP/1.1" );
      c.println( "Content-Type: application/x-www-form-urlencoded" );
      c.print( "Content-Length: " );
      c.println(le);
      c.print( "Host: " );
      c.println( SITE_URL );
      c.println();
      c.println( payload );

      int v;
      while(c.available()){
        v = c.read();
        if(v < 0){
          Serial.println("No response.");
          break;
        }
        Serial.print((char)v);
      }
      delay(1000);
}
void printRespone(){
  // Make sure we are connected, and dump the response content to Serial
  while (c)
  {
    int v = c.read();
    if (v != -1)
    {
      Serial.print((char)v);
    }
    else
    {
//      Serial.println("no more content, disconnect");
//      c.stop();
//      while (1)
//      {
//        delay(1);
//      }
    }
  }
}
int smRead( int pin ){ // Pass testing

  uint32_t soilMois = 0;
  // Print Header
  Serial.println("--------------");

  // Soil Moisture
  soilMois = analogRead( pin );
  Serial.print( "Soil Moisture: " );
  Serial.println( soilMois );

  delay ( 1000 );
  return soilMois;
}
int lightRead( int pin ){ // Pass testing
  uint32_t light = 0;
  // Light
  light =  analogRead( analogPinLight );;
  Serial.print( "Light: " );
  Serial.println( light );

  delay ( 1000 );
  return light;
}

boolean airReadFirstTime = true;
float airRead( LDHT dht, int type ) // Pass testing
{

  float rst = 0.0;
//  int airReadErrorCnt = 0;

  Serial.println( "Air ");
  // Air
  int v = dht.read();

  // Reading Fail Handling & First time is alway correct reading
  while ( v == 0 )
  {
    Serial.println( "DHT readinng fails, re-try ");
    delay ( 3000 );
    v = dht.read();
//    airReadErrorCnt++;
  }
  // Reading Succuess
  if( v == 1 )
  {
    if( type == 0 )
    {
      rst = dht.readTemperature();
      delay ( 1000 );
      Serial.print( "Temp: ");
      Serial.println( rst );

      // Buffering previous value
      // previousTemp = rst;
    }
    else if ( type == 1 )
    {
      rst = dht.readHumidity();
      delay ( 1000 );
      Serial.print( "Mois: ");
      Serial.println( rst );
      // Buffering previous value
      // previousMois = rst;
    }
    else
    {
      rst = -1;
    }
  }

  airReadFirstTime = false;

  return rst;

}
