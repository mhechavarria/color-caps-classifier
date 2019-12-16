void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(30000);
  
  Serial.write("g");
  delay(30000);

  Serial.write("v");
  delay(30000);

  Serial.write("r");
  delay(30000);
  
  Serial.write("n");
  delay(30000);

  Serial.write("y");
  delay(30000);

  Serial.write("a");
}
