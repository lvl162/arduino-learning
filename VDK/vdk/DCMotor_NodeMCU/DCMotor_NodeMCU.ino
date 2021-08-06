const int In3 = 2;
const int In4 = 0;
uint8_t Sp = 4;
void setup() {
  Serial.begin(9600);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  //pinMode(Sp, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int speed;
//   if (Serial.available()) {
//       speed = Serial.parseInt();
////      if (speed >= 0 && speed <= 255) {
////         analogWrite(motorPin, speed);
////      }
//    Serial.println(speed);
    digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(Sp, speed);
  delay(200);
  
  //Serial.println(digitalRead(In3) + " " + digitalRead(In4));
//    }
    
}
