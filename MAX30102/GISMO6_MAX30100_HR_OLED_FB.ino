#include "Credentials.h"

#include "MAX30105.h"

#include "heartRate.h"
MAX30105 particleSensor;
String tag = "IOTLAB/HeartBeat/HR";

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
int beatCount;
int loopCount;

void WiFiInit();
void OLEDInit();
void OLEDUpdate();
void FirebaseInit();
void FirebaseWrite();


void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  WiFiInit();
  FirebaseInit();
  OLEDInit();
}

void loop()
{
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
     
      beatCount++;
      if(beatCount == 4)
      {
       Serial.print("Avg BPM=");
       Serial.print(beatAvg);

        OLEDUpdate();
        FirebaseWrite();
        beatCount = 0;
      }
    }
  }

 
 
  if (irValue < 50000)
    {
     loopCount++;
     if(loopCount == 10){
      loopCount = 0;
     Serial.println(" No finger?");
     display.clear();
     display.drawString(0,0,"No Finger?");
     display.display();
     FirebaseWriteNF();
    }
    delay(100);
    }
  
}
void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
}

void OLEDUpdate(){
  display.clear();
  display.drawString(0,0,"Heart Rate:");
  display.drawString(40,30,String(beatAvg));
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
  Firebase.setString(firebaseData,tag,String(beatAvg));
 
}
void FirebaseWriteNF(){
  Firebase.setString(firebaseData,tag,"No_Finger?");
 
}

  
  
