#define BUZZER_PIN 32
#define BUZZER_CHANNEL 0
void setup(){
  
  }
void loop(){
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  ledcWriteTone(BUZZER_CHANNEL,1500);
  delay(3000);
  ledcDetachPin(BUZZER_PIN);
  delay(3000);
}
