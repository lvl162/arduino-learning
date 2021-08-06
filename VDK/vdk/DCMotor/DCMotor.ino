const int In3 = 8;
const int In4 = 7;

const int Led1 = 12;
const int Led2 = 13;

const int Motor1 = 5;
const int BienTro = A0;
const int but = 2;

int tmp;

void setup() {
  Serial.begin(9600);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Motor1, OUTPUT);
  pinMode(but, INPUT);
  tmp = digitalRead(but);
  

}

void loop() {
  int speed;
   if (Serial.available()) {
       speed = Serial.parseInt();
//      if (speed >= 0 && speed <= 255) {
//         analogWrite(motorPin, speed);
//      }
    Serial.println(speed);}
  int valBut = digitalRead(but);
//  tmp = 1;
//  int valBut = 1;
//  int speed = 100;
  if (tmp != valBut){
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    delay(1500);
    tmp = valBut;
  }
//  int value = analogRead(bientro);
//  int speed = map(value, 0,1023, 0, 255);
  tmp = valBut;
  if (tmp == 1) {
  
//  digitalWrite(Led2, LOW);
//  digitalWrite(Led1, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(Motor1, speed);
  
  }
  else {
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  analogWrite(Motor1, speed);
  }
}
