#include <WiFi.h>
#include "time.h"
#include "Credentials.h"

#define relayPin 13
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec =  0;

int hrs;
int mins;
int secs;

int delayTime = 3000;


void getCurrentTimeNow();
void WiFiInit();
void OLEDInit();
void OLEDUpdate();
void FirebaseInit();
void FirebaseUpdate();



void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  WiFiInit();
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getCurrentTimeNow();

  OLEDInit();
  FirebaseInit();
  }

void loop()
{
   char buffer[10];

  /* sprintf(buffer,"%02d-%02d-%02d",now.hour(),now.minute(),now.second());
   Serial.println(buffer);
    
   Firebase.setString(firebaseData,"IOTLAB/Appliance_Control/Current_Time",buffer);*/

   
  getCurrentTimeNow(); 
  sprintf(buffer,"%02d-%02d-%02d",hrs,mins,secs);
  Serial.println(buffer);
  Firebase.setString(firebaseData,"IOTLAB/Appliance_Control/Current_Time",buffer);

  display.clear();
  display.drawString(0,0,buffer);
   
   int currentTimeTotal;
   currentTimeTotal = hrs*60 + mins;
   Serial.println(currentTimeTotal);
    
   String startTimeFull;
   String startTime;
   int startTimeHrs,startTimeMins,startTimeTotal;
   Firebase.getString(firebaseData,"IOTLAB/Appliance_Control/Start_Time",startTimeFull);
   startTime=startTimeFull.substring(2,startTimeFull.length()-2);
   //Serial.println(startTime);
   display.drawString(0,30,startTime);
   startTimeHrs = startTime.substring(0,2).toInt();
   //Serial.println(startTimeHrs);
   startTimeMins = startTime.substring(3).toInt();
   //Serial.println(startTimeMins);
   startTimeTotal=startTimeHrs*60 + startTimeMins;
   Serial.println(startTimeTotal);


   String endTimeFull;
   String endTime;
   int endTimeHrs,endTimeMins,endTimeTotal;
   Firebase.getString(firebaseData,"IOTLAB/Appliance_Control/End_Time",endTimeFull);
   endTime=endTimeFull.substring(2,endTimeFull.length()-2);
   //Serial.println(endTime);
    display.drawString(80,30,endTime);
   endTimeHrs = endTime.substring(0,2).toInt();
   //Serial.println(endTimeHrs);
   endTimeMins = endTime.substring(3).toInt();
   //Serial.println(endTimeMins);
   endTimeTotal=endTimeHrs*60 + endTimeMins;
   Serial.println(endTimeTotal); 

   if((currentTimeTotal >= startTimeTotal) && (currentTimeTotal < endTimeTotal)){
    digitalWrite(relayPin,HIGH);
    Serial.println("Appliance ON"); 
    display.setColor(WHITE);
    display.drawCircle(60, 36, 8);
    display.fillCircle(60,36,8);
    Firebase.setInt(firebaseData,"IOTLAB/Appliance_Control/Appliance_Status",1);
   }
   else{
    digitalWrite(relayPin,LOW);
    Serial.println("Appliance OFF");
    display.setColor(BLACK);
    display.drawCircle(60, 36, 8);
    display.fillCircle(60,36,8);
    display.setColor(WHITE);
    display.drawCircle(60, 36, 8);
    Firebase.setInt(firebaseData,"IOTLAB/Appliance_Control/Appliance_Status",0);
    }

   
   
  display.display();   
  delay(delayTime); 

  
  
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
void OLEDInit(){
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.drawString(0,0,"Warming up...");
  display.display();
}

void OLEDUpdate(){
  display.clear();
 // display.drawString(0,0,magswStatus);
 // display.drawString(0,30,PIRStatus);
  display.display();
}
void FirebaseInit(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void getCurrentTimeNow()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  
  hrs = timeinfo.tm_hour;
  mins = timeinfo.tm_min; 
  secs = timeinfo.tm_sec;

  Serial.print("Hours:");
  Serial.println(hrs);

  Serial.print("Minutes:");
  Serial.println(mins);

  Serial.print("Seconds:");
  Serial.println(secs);
}
