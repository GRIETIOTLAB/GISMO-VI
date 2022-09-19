#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#include "SSD1306.h"
SSD1306 display(0x3c,21,22);
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;

float heartRate;


void OLEDInit();
void OLEDUpdate(); 

void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);

    OLEDInit();
}
 
void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        heartRate = pox.getHeartRate();
        Serial.print("Heart rate:");
        Serial.print(heartRate);
        Serial.println("bpm");
        
        tsLastReport = millis();
        OLEDUpdate();
    }
}
void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
}

void OLEDUpdate(){
  
  display.clear();
  display.drawString(0,0,"HR : "+String(heartRate));
  display.display();
}
