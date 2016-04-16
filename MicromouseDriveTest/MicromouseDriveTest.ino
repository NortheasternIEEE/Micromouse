void setup() {
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  analogWrite(A1, 255);
  analogWrite(A2, 255);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(10, LOW);

 
  delay(1000);
  /*
  digitalWrite(6, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(10, HIGH);

  delay(1000);
  */
}
