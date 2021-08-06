void setup() {
pinMode(7, INPUT); // OUTPUT vào D7
Serial.begin(9600);
}
void loop() {
Serial.println(digitalRead(7));
//delay(100);
}
