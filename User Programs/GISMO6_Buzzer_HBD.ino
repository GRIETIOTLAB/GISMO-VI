#define BUZZER_PIN 32
#define BUZZER_CHANNEL 0
#include <Wire.h>
#include "SSD1306.h"

SSD1306 display(0x3c,21,22);
String myString;

     void setup()
     {
       OLEDInit();
     }

      void OLEDInit()
      {  display.init();
        display.setFont(ArialMT_Plain_24);
      }

      void OLEDUpdate()
      {  display.clear();
        display.drawString(0,0,myString);
        display.display();
      }

     void J_Note_Play(int, int, char[]);
   
     void J_Note_Play(int d1, int d2,  char c[4])
     { int freq;
       myString = c;
       OLEDUpdate();
       
           if  (myString == "C4")freq = 262;
      else if  (myString == "C#4")freq = 277;
      else if  (myString == "D4")freq = 294;
      else if  (myString == "D#4")freq = 311;
      else if  (myString == "E4")freq = 330;
      else if  (myString == "F4")freq = 349;
      else if  (myString == "F#4")freq = 370;
      else if  (myString == "G4")freq = 392;
      else if  (myString == "G#4")freq = 415;

      else if  (myString == "A#4")freq = 466;
      else if  (myString == "B4")freq = 494;
      else if  (myString == "C5")freq = 523;

     else if  (myString == "C#5")freq = 554;

   
 
      ledcDetachPin(BUZZER_PIN);
      delay(d1);
      ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
      ledcWriteTone(BUZZER_CHANNEL,freq);
      delay(d2);
     }



void loop(){
   
     J_Note_Play(10,500,"C#4");
     J_Note_Play(10,500,"C#4");
     J_Note_Play(10,1000,"D#4");
     J_Note_Play(10,1000,"C#4");
     J_Note_Play(10,1000,"F#4");
     J_Note_Play(10,1000,"F4");
   
     J_Note_Play(10,500,"C#4");
     J_Note_Play(10,500,"C#4");
     J_Note_Play(10,1000,"D#4");
     J_Note_Play(10,1000,"C#4");
     J_Note_Play(10,1000,"G#4");
     J_Note_Play(10,1000,"F#4");
 
     J_Note_Play(10,500,"C#4");
     J_Note_Play(10,500,"C#4");
     J_Note_Play(10,1000,"C#5");
     J_Note_Play(10,1000,"A#5");
     J_Note_Play(10,1000,"F#4");
     J_Note_Play(10,1000,"F4");
     J_Note_Play(10,1000,"D#4");

     J_Note_Play(10,500,"B4");
     J_Note_Play(10,500,"B4");
     J_Note_Play(10,1000,"A#4");
     J_Note_Play(10,1000,"F#4");
     J_Note_Play(10,1000,"G#4");
     J_Note_Play(10,1000,"F#4");
      delay(500);
      ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
 
 
}
