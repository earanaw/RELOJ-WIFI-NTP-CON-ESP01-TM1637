//============================ LIBRERIAS =====================================
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TM1637Display.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

//========================= Credenciales de WiFi==============================
#define WIFI_SSID "Imperio II"
#define WIFI_PASSWORD "20S1stemas"
// #define ledServer 1
int lastTime;
int currentTime;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

// #define CLK  2
// #define DIO  0

#define CLK 2   // define CLK pin TX pin (any digital pin)
#define DIO 0   // define DIO pin RX (any digital pin)



TM1637Display display = TM1637Display(CLK, DIO);
//================================================================================
//      SETUP
//================================================================================

void setup() {
  Serial.begin(115200);
  Serial.println();

  // pinMode(ledServer, OUTPUT);
    
//================================================================================
//      INICIALIZAR WIFI
//================================================================================
 // attempt to connect to Wifi network:
  Serial.print("Conectando al Wifi de: ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    // digitalWrite(ledServer, LOW);
  }
  delay(0);
  // digitalWrite(ledServer, HIGH);
  Serial.println("\nConectado al WiFi");
  Serial.print("Dirección IP: "); 
  Serial.println(WiFi.localIP());

  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(-18000);

  display.clear();
  display.setBrightness(2);

}

//================================================================================
//      LOOP
//================================================================================
void loop(){ 

  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  int numHoras = timeClient.getHours();
  int numMinutos = timeClient.getMinutes();
  // int numMinutos = random(0, 60);
  currentTime =  (numHoras * 100) + numMinutos;
  
  if(currentTime != lastTime){
    Serial.print("time: ");
    Serial.println(currentTime);  
    display.showNumberDecEx(currentTime, 0b01000000, true, 4, 0);    
      
  }

    lastTime = currentTime;

}    

