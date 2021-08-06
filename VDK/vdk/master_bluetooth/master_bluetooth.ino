#define ledPin 9
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); //RX 11 TX 10

// USB 1
void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);

}
void loop() {
//  int a = analogRead(A0);
//  int v = map(a, 0, 1023, 0, 180);
//  String s = String(v);
  
//  BT.println(s);
//  if (BT.available()) {
//      int in = BT.parseInt();
//      Serial.println(in);
//      digitalWrite(13, in);
//    }
//  delay(1000);
  BT.write('1');
    delay(1000);
}
