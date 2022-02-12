#define magSwitch 16
#define PIR 33
#define LED 2
int loopDelay = 1000;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(magSwitch,INPUT_PULLUP);
  pinMode(PIR,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  // Initial warmup period of 1 minute for PIR sensor
  Serial.print("Warming up...");
  for(int i = 0; i < 60; i++){
    digitalWrite(2,!digitalRead(2));
    Serial.print(".");
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
// Mag switch reading 
 int sw_status = digitalRead(16);
 if(sw_status == HIGH)
 Serial.println("OPEN");
 else
 Serial.println("CLOSED");

// PIR sensor reading
  int pir_status = digitalRead(PIR);
  if (pir_status == HIGH) {
    Serial.println("Motion detected!");
    loopDelay=3000;
    }
  else {
    Serial.println("No Motion detected!");
    loopDelay = 1000;
    }

 delay(loopDelay);
}
