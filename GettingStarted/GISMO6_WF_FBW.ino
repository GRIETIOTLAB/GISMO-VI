#include <WiFi.h>
#include "FirebaseESP32.h"
#define FIREBASE_HOST "radsproject.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "4niCZOkFw4C2WVZf04gk9PrQx9isMG7NbCva9CmU"
#define WIFI_SSID "rads_home"
#define WIFI_PASSWORD "rads1961"
//Define Firebase Data object
FirebaseData firebaseData;

float val = 0.0;
String tag = "IOTLAB/My_App/Sensor_Value";
void setup() {

  Serial.begin(115200);
  WiFiInit();
  FirebaseInit();
  }

void loop() {
   FirebaseWrite();
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
