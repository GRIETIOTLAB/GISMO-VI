/* Soil Moisture sensor pin   : GPIO34
 * Relay pin                  : GPIO13
 *
  */
#include "SSD1306.h"
SSD1306 display(0x3c,21,22);  
#define smPin 34
#define relayPin 13
int smValue;
int smLimit = 1500;
int delayTime = 2000;
String motorStatus = "OFF";
void OLEDInit();
void OLEDUpdate();

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin,OUTPUT);
  Serial.begin(115200);
  OLEDInit();
  }

void loop() {
  // put your main code here, to run repeatedly:
smValue = 4095 - analogRead(smPin);
Serial.print("Soil Moisture = ");
Serial.println(smValue);

if (smValue < smLimit){
digitalWrite(relayPin,HIGH);
Serial.println("Motor turned ON");
motorStatus = "ON";
}
else{
digitalWrite(relayPin,LOW);
Serial.println("Motor turned OFF");
motorStatus = "OFF";
}

OLEDUpdate();
delay(delayTime);
}

void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
}

void OLEDUpdate(){
  
 
  display.clear();
  display.drawString(30,0,String(smValue));
  display.drawString(30,30,String(motorStatus));
  display.display();
}
  
