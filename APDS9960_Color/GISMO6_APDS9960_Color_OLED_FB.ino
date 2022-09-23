/****************************************************************
ColorSensor.ino
APDS-9960 RGB and Gesture Sensor
Shawn Hymel @ SparkFun Electronics
October 15, 2014
https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor

Tests the color and ambient light sensing abilities of the 
APDS-9960. Configures APDS-9960 over I2C and polls the sensor for
ambient light and color levels, which are displayed over the 
serial console.

Hardware Connections:

IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock

Resources:
Include Wire.h and SparkFun_APDS-9960.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with SparkFun Arduino Pro Mini 3.3V

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.
****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include "Credentials.h"


 
// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
void OLEDInit();
void OLEDUpdate(); 
void WiFiInit();
void FirebaseInit();
void FirebaseWrite();
String tagAmbient = "IOTLAB/Color/Ambient";
String tagRed = "IOTLAB/Color/Red";
String tagGreen = "IOTLAB/Color/Green";
String tagBlue = "IOTLAB/Color/Blue";
void setup() {
  
  // Initialize Serial port
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ColorSensor"));
  Serial.println(F("--------------------------------"));
  
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  
  // Wait for initialization and calibration to finish
  delay(500);
   OLEDInit();
   WiFiInit();
 FirebaseInit();
}

void loop() {
  
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readAmbientLight(ambient_light) ||
        !apds.readRedLight(red_light) ||
        !apds.readGreenLight(green_light) ||
        !apds.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    Serial.print("Ambient: ");
    Serial.print(ambient_light);
    Serial.print(" Red: ");
    Serial.print(red_light);
    Serial.print(" Green: ");
    Serial.print(green_light);
    Serial.print(" Blue: ");
    Serial.println(blue_light);
    OLEDUpdate();
    FirebaseWrite();
  }
   
  // Wait 1 second before next reading
  delay(2000);
}

void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_16);
}

void OLEDUpdate(){
  
  display.clear();
  display.drawString(0,0,"AMB : "+String(ambient_light));
  display.drawString(0,16,"R : "+String(red_light));
  display.drawString(0,32,"G : "+String(green_light));
  display.drawString(0,48,"B : "+String(blue_light));
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
  Firebase.setInt(firebaseData,tagAmbient,ambient_light);
  Firebase.setInt(firebaseData,tagRed,red_light);
  Firebase.setInt(firebaseData,tagGreen,green_light);
  Firebase.setInt(firebaseData,tagBlue,blue_light);
 
}
