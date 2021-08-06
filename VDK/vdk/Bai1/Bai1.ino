const int loa = 6;
const int red = 13;
const int blue = 12;
const int yellow = 11;

const int sw = 2;

const int In3 = 3;
const int In4 = 4;

const int Motor = 5;

const int button = 7;

const int BienTro = A0;

const int Trig = 9;
const int Echo = 10;

int isDoiChieu;
int isLedOn;
int isChikai1;
void setup() {
  pinMode(loa, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(button, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  analogWrite(Motor, 0);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);


  isDoiChieu = digitalRead(sw);
  Serial.begin(9600);
}
int isChikai() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long duration = pulseIn(Echo, HIGH);
  float dis = duration / 2 / 29.412;
  Serial.println(dis);
  return dis < 15.0;
}
void DoiChieu() {
  if (digitalRead(sw) != isDoiChieu) {
    // Doi chieu
    int in3 = digitalRead(In3);
    int in4 = digitalRead(In4);
    digitalWrite(In3, 0);
    digitalWrite(In4, 0);
    delay(500);

    digitalWrite(In3, !in3);
    digitalWrite(In4, !in4);
    analogWrite(Motor, 100);
    isDoiChieu = digitalRead(sw);
  }
}

void Led12On() {
  digitalWrite(red, 1);
  delay(100);
  digitalWrite(red, 0);
  digitalWrite(blue, 1);
  delay(100);
  digitalWrite(blue, 0);

}

int ChangeSpeed() {

  int speed = map(analogRead(BienTro), 0, 1023, 0, 255);

  return speed;

}

void loop() {

  // sw 0 1
  //    Serial.println(digitalRead(sw));
  DoiChieu();
  ChangeSpeed();

  isLedOn = digitalRead(button);
  //        Serial.println(isLedOn);

  if (isLedOn && !isChikai()) {
    analogWrite(Motor, ChangeSpeed());
    digitalWrite(loa, 0);
    digitalWrite(yellow, 0);
    Led12On();
  }
  if (isLedOn && isChikai()) {
    digitalWrite(loa, 1);
    digitalWrite(Motor, 0);
    digitalWrite(yellow, 1);
    }
  if (!isLedOn) {
    analogWrite(Motor, 0);
    digitalWrite(loa, 0);
    digitalWrite(yellow, 0);
    }


}
