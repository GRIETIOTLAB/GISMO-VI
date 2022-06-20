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
       
           if  (myString == "S1")freq = 240;
      else if  (myString == "R1")freq = 270;
      else if  (myString == "G1")freq = 300;
      else if  (myString == "M1")freq = 330;
      else if  (myString == "P1")freq = 360;
      else if  (myString == "D1")freq = 400;
      else if  (myString == "N1")freq = 440;
      else if  (myString == "S2")freq = 480;
      else if  (myString == "R2")freq = 540;
      else if  (myString == "G2")freq = 600;
      else if  (myString == "M2")freq = 660;
 
      ledcDetachPin(BUZZER_PIN);
      delay(d1);
      ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
      ledcWriteTone(BUZZER_CHANNEL,freq);
      delay(d2);
     }



void loop(){
   
     J_Note_Play(10,500,"S1");
     J_Note_Play(10,500,"R1");
     J_Note_Play(10,500,"G1");
     J_Note_Play(10,500,"M1");
     J_Note_Play(10,500,"P1");
     J_Note_Play(10,500,"D1");
     J_Note_Play(10,500,"N1");
     J_Note_Play(10,1000,"S2");
 

     J_Note_Play(10,500,"S2");
     J_Note_Play(10,500,"N1");
     J_Note_Play(10,500,"D1");
     J_Note_Play(10,500,"P1");
     J_Note_Play(10,500,"M1");
     J_Note_Play(10,500,"G1");
     J_Note_Play(10,500,"R1");
     J_Note_Play(10,1000,"S1");
   
}
