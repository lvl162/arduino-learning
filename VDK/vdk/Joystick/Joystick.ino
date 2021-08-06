const int x = 1, y = 0, z = 3;
void setup() {
    pinMode(z, INPUT_PULLUP);
    Serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Vx, Vy, Vz;
  Vx = analogRead(x);
  Vy = analogRead(y);
  Vz = digitalRead(z);
  Serial.println(Vx);

  Serial.println(Vy);

  Serial.println(Vz);
  digitalWrite(13, !Vz);
  Serial.println("\n\n");
  delay(200);
}
