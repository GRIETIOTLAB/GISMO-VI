#define BUZZER_PIN 32

void setup(){
  
  }
void loop(){
  ledcAttach(BUZZER_PIN,1500,12);
  ledcWriteTone(BUZZER_PIN,1500);
  delay(3000);
  ledcDetach(BUZZER_PIN);
  delay(3000);
}
