void setup() {
  // put your setup code here, to run once:
  pinMode(16,INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 int sw_status = digitalRead(16);
 if(sw_status == HIGH)
 Serial.println("OPEN");
 else
 Serial.println("CLOSED");
 delay(1000);
}
