#include <WiFi.h>
#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxx"

void setup() {
  Serial.begin(115200);
  WiFiConnect();
 }

void loop() {
 
}

void WiFiConnect(){
//Connecting to Wi-Fi network
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
