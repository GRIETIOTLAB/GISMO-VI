#include "font_5x4.h"
#include <HT1632.h>
#include "Credentials.h"

int i = 0;
int wd;
int count;
int humidity,temperature;
char msg[] = "H:56 T:23";
void WiFiinit();
FirebaseData firebaseData;
void setup () {
  Serial.begin(115200);
  HT1632.begin(22,5,13);
  WiFiInit();
  
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  wd = HT1632.getTextWidth(msg, FONT_5X4_WIDTH, FONT_5X4_HEIGHT);
}

void loop () {
  
  
  HT1632.drawTarget(BUFFER_BOARD(1));
  HT1632.clear();
  HT1632.drawText(msg, OUT_SIZE - i, 1, FONT_5X4, FONT_5X4_WIDTH, FONT_5X4_HEIGHT, FONT_5X4_STEP_GLYPH);
  HT1632.render();
  
  
  
  i = (i+1)%(wd + OUT_SIZE );
 
  delay(200);
  count++;
  if(count == 25){
    count = 0;
    getAmbientParameters();
  }

  
}
void WiFiInit(){
  pinMode(25,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(25,!digitalRead(2));
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
   
}

void getAmbientParameters()
{
Firebase.getInt(firebaseData,"IOTLAB/Ambient_Parameters/Humidity",humidity);
Serial.println(humidity);
msg[2] = (humidity/10) + 48;
Serial.println(msg[2]);
msg[3] = (humidity%10) + 48;
Serial.println(msg[3]);
 
Firebase.getInt(firebaseData,"IOTLAB/Ambient_Parameters/Temperature",temperature);
Serial.println(temperature);
msg[7] = (temperature/10) + 48;
Serial.println(msg[7]);
msg[8] = (temperature%10) + 48;
Serial.println(msg[8]);

  
}
