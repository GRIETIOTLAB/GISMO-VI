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
#include "model2.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // I2C

Eloquent::ML::Port::LinearRegression lr;

#define SEALEVELPRESSURE_HPA (1013.25)
float tempC,tempF,atPressure,altitude,humidity;
float temperature[4];
int i;

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

   for(i = 0;i < 4;i++){
    temperature[i] = bmp.readTemperature();
    delay(2000);
     }
}

void loop() {

 float predictedTemp = lr.predict(temperature);
 float sensorTemp = bmp.readTemperature();

 for(i = 0;i < 3;i++){
  temperature[i] = temperature[i+1];
 }
 temperature[3]=sensorTemp;
 Serial.print(predictedTemp);
 Serial.print('\t');
 Serial.println(sensorTemp);
 delay(2000);
}
void printValues(){
 
  Serial.print("Temperature = ");
  tempC = bmp.readTemperature();
//Serial.print(bme.readTemperature());
Serial.print(tempC);
Serial.println(" deg C");


Serial.print("Temperature = ");
Serial.print(1.8*tempC+32);
Serial.println(" deg F");

Serial.print("Pressure = ");
atPressure=bmp.readPressure()/100.0F;
Serial.print(atPressure);
Serial.println(" hPa");


Serial.print("Altitude = ");
altitude=bmp.readAltitude(SEALEVELPRESSURE_HPA);
Serial.print(altitude);
Serial.println(" m");
Serial.println();

}
