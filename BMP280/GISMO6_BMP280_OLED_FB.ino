/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; // I2C
#include "Credentials.h"

#define SEALEVELPRESSURE_HPA (1013.25)

float tempC,tempF,atPressure,altitude,humidity;
void setup() {
  Serial.begin(115200);
  Serial.println(F("BMP280 test"));

  if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
      Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

 OLEDInit();
 WiFiInit();
 FirebaseInit();
}

void loop() {
    printValues();
    displayValues();
    delay(2000);
}

 void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_16);
}

void printValues(){
 // float tempC,tempF,atPressure,altitude,humidity;
  Serial.print("Temperature = ");
  tempC = bmp.readTemperature();
//Serial.print(bme.readTemperature());
Serial.print(tempC);
Serial.println(" deg C");
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Temperature",tempC);

Serial.print("Temperature = ");
//Serial.print(1.8*bme.readTemperature()+32);
Serial.print(1.8*tempC+32);
Serial.println(" deg F");

Serial.print("Pressure = ");
atPressure=bmp.readPressure()/100.0F;
//Serial.print(bme.readPressure()/100.0F);
Serial.print(atPressure);
Serial.println(" hPa");
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Pressure",atPressure);

Serial.print("Altitude = ");
altitude=bmp.readAltitude(SEALEVELPRESSURE_HPA);
//Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
Serial.print(altitude);
Serial.println(" m");
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Altitude",altitude);
Serial.println();
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Humidity",0.0);

}

void displayValues(){
  display.clear();
  
  String myString = "";
  
  char buffer[6];
  dtostrf(tempC,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" C");
  display.drawString(0,0,myString);

  humidity = 0.0;
  myString = "";
  dtostrf(humidity,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" %");
  display.drawString(64,0,myString);

 myString = "";
  dtostrf(atPressure,5,1,buffer);
  myString.concat(buffer);
   display.drawString(0,30,myString);

    myString = "";
  dtostrf(altitude,5,1,buffer);
  myString.concat(buffer);
  myString.concat("m");
   display.drawString(64,30,myString);


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
