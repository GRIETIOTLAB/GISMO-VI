#define magSwitch 16
#define PIR 33
#define LED 2


#include "Credentials.h"

String magswStatus;
String PIRStatus;

int loopDelay = 1000;

void OLEDInit();
void OLEDUpdate();
void WiFiinit();
void FirebaseInit();
void FirebaseWrite();

String tag1 = "IOTLAB/HSS/MagswStatus";
String tag2 = "IOTLAB/HSS/PIRSwitch"; 
void setup() {
  // put your setup code here, to run once:
  pinMode(magSwitch,INPUT_PULLUP);
  pinMode(PIR,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  OLEDInit();
  WiFiInit();
  FirebaseInit();

  // Initial warmup period of 1 minute for PIR sensor
  for(int i = 0; i < 60; i++){
    digitalWrite(2,!digitalRead(2));
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
// Mag switch reading 
 int sw_status = digitalRead(16);
 if(sw_status == HIGH){
 Serial.println("OPEN");
 magswStatus = "Window_Open";}
 else{
 Serial.println("CLOSED");
 magswStatus = "Window_Closed";}

// PIR sensor reading
  int pir_status = digitalRead(PIR);
  if (pir_status == HIGH) {
    Serial.println("Motion detected!");
    PIRStatus = "Motion_detected";
    loopDelay = 3000;
    }
  else {
    Serial.println("No Motion");
    PIRStatus = "No_Motion";
    loopDelay = 1000;
    }
OLEDUpdate();
FirebaseWrite();
 delay(loopDelay);
}
void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.drawString(0,0,"Warming up...");
  display.display();
}

void OLEDUpdate(){
  display.clear();
  display.drawString(0,0,magswStatus);
  display.drawString(0,30,PIRStatus);
  display.display();
}
void WiFiInit(){
  pinMode(2,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(2,!digitalRead(2));
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
  Firebase.setString(firebaseData,tag1,magswStatus);
  Firebase.setString(firebaseData,tag2,PIRStatus);
 
}
  
  
