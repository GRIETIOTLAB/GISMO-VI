#include <WiFi.h>
#include "FirebaseESP32.h"
#include "SSD1306.h"

SSD1306 display(0x3c,21,22);

#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

float val = 0.0;
String tag = "IOTLAB/My_App/Sensor_Value";
void setup() {

  Serial.begin(115200);
  WiFiInit();
  FirebaseInit();
  OLEDInit();
  }

void loop() {
   FirebaseWrite();
   OLEDUpdate();
   Serial.println(val);
   val = val + 1.54;
   if(val > 10.0) val = 0.0;
   delay(1000);
}
void WiFiInit(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
   
}
void FirebaseInit(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}
void FirebaseWrite(){
  Firebase.setFloat(firebaseData,tag,val);
 
}
void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
}

void OLEDUpdate(){
  display.clear();
  display.drawString(0,0,String(val));
  display.display();
}
  
