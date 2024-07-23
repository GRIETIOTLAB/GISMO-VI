
#include "SSD1306.h"

SSD1306 display(0x3c,21,22);

String pirString;


void setup() {
  // put your setup code here, to run once:
  
  pinMode(33,INPUT);
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  digitalWrite(2,HIGH);
  delay(20000);
  digitalWrite(2,LOW);
  OLEDInit();

}

void loop() {
  // put your main code here, to run repeatedly:
int pirState = digitalRead(33);
if(pirState == HIGH)
{
  pirString = "Motion detected"; 
  Serial.println("Motion detected");
  OLEDUpdate();
  delay(1000);
}
else
{
  pirString = "No motion";
  Serial.println("No motion detected");
  OLEDUpdate();
}
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
  display.drawString(0,30,pirString);
  display.display();
}
  
