#define magSwitch 16
#define PIR 33
#define LED 2

#include "SSD1306.h"

SSD1306 display(0x3c,21,22);

String magswStatus;
String PIRStatus;

int loopDelay = 1000;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(magSwitch,INPUT_PULLUP);
  pinMode(PIR,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  OLEDInit();
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
 magswStatus = "Window Open";}
 else{
 Serial.println("CLOSED");
 magswStatus = "Window Closed";}

// PIR sensor reading
  int pir_status = digitalRead(PIR);
  if (pir_status == HIGH) {
    Serial.println("Motion detected!");
    PIRStatus = "Motion detected";
    loopDelay = 3000;
    }
  else {
    Serial.println("No Motion detected!");
    PIRStatus = "No Motion";
    loopDelay = 1000;
    }
OLEDUpdate();
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
  
