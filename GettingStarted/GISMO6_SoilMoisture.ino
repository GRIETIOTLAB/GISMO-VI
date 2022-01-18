void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
  }

void loop() {
  // put your main code here, to run repeatedly:
  int smValue = 4095 - analogRead(34);
  Serial.println(smValue);
  delay(1000);
}
