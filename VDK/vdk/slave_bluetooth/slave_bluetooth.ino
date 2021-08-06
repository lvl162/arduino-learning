#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);
#include <Servo.h>
// USB 0
Servo myServo;
String data = "";
void setup() {
  BT.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  Serial.begin(9600);
  myServo.attach(9);
}
void loop() {
//  if (BT.available()) {
//    //    String test = "";
//    //    while (BT.available()>0) {
//    //      char in = BT.read();
//    //
//    //      if (in == '\n') {
//    //        Serial.println(test);
//    //        test = "";
//    //        }
//    //        test = test + (String)in;
//    //      }
//    int a = BT.parseInt();
//    Serial.println(a);
//    BT.println(digitalRead(12));
//    //
//    //    //
//    //    int a = buffer.toInt();
//    //
//         myServo.write(a);
//    //
//    //    Serial.println("DONE");
//    //    BT.write('!');
//  }
//  delay(100);
    if (BT.available()) {
      Serial.println(BT.read());
      }
      delay(200);
}
