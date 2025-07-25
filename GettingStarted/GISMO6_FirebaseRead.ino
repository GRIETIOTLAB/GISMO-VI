#include <Wire.h>


#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

int delayTime = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(115200);


 //Connecting to Wi-Fi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(2,!digitalRead(2));
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  
}

void loop() {
  // put your main code here, to run repeatedly:

String lightCmdFull;
String lightCmd;
int finalCmd;


Firebase.getString(firebaseData,"IOTLAB/My_App/Motor_Cmd",lightCmdFull);
Serial.println(lightCmdFull);  
lightCmd = lightCmdFull.substring(2,lightCmdFull.length()-2);
Serial.println(lightCmd);  
finalCmd = lightCmd.toInt();

if(lightCmd == "1")
{
  digitalWrite(2,HIGH);
  digitalWrite(13,LOW);
  Serial.println("Light ON");
  
}
else
{
   digitalWrite(2,LOW);
   digitalWrite(13,HIGH);
  Serial.println("Light OFF");
    
}


 
delay(delayTime);
}
