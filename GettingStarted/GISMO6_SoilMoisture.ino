int threshold = 1500;
void setup() {
  // put your setup code here, to run once:
    pinMode(2,OUTPUT);
    Serial.begin(115200);
  }

void loop() {
  // put your main code here, to run repeatedly:
  int smValue = 4095 - analogRead(34);
  Serial.print("Soil moisture value = ");
  Serial.println(smValue);
  if(smvalue < threshold)
  {
    digititalWrite(2,HIGH);
    Serial.println("Soil dry");
  }
  else
  {
    digitalWrite(2,LOW);
    Serial.println("Soil wet");
  }
  delay(1000);
}

