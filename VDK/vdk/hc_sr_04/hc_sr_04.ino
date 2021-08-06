int trig = 5;
int led = 13;
int echo = 3;
long duration;
float dis;
void setup()
{
  pinMode(led, OUTPUT);
   pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
Serial.begin(9600);
  
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  dis = duration/2/29.412;
  if (dis < 5) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
  Serial.print(dis);
  Serial.println("cm");
  delay(500);

}
