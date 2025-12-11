void setup() {
  Serial.begin(9600);
}

void loop() {
  int ACP = analogRead(A0);
  Serial.println(ACP);
  delay(3000);
}
