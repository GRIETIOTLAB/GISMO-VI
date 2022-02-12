#include <WiFi.h>
#include "time.h"
#include "Credentials.h"


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec =  0;

int hrs;
int mins;

int getCurrentHrsMins()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return 0;
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  
  hrs = timeinfo.tm_hour;
  mins = timeinfo.tm_min; 

  Serial.print("Hours:");
  Serial.println(hrs);

  Serial.print("Minutes:");
  Serial.println(mins);

  return (hrs * 60 + mins);

}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  WiFiInit();
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getCurrentHrsMins();

  }

void loop()
{
  delay(1000);
  Serial.println(getCurrentHrsMins());
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
