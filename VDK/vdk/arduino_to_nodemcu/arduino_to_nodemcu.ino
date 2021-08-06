#include <SoftwareSerial.h>
#include<Servo.h>
Servo myServo;
int in3 = 7;
int in4 = 8;
int motor = 6;
int motor_speed = 255;
SoftwareSerial s(10, 11);
#include <ArduinoJson.h>
void setup() {
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(motor, OUTPUT);
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  //  while (!Serial) continue;
  myServo.attach(9);

}

void loop() {
  // StaticJsonBuffer<1000> jsonBuffer;
  //  JsonObject& root = jsonBuffer.parseObject(s);
  //  if (root == JsonObject::invalid())
  //    return;
  //
  //  Serial.println("JSON received and parsed");
  //  root.prettyPrintTo(Serial);
  //  Serial.print("Data 1 ");
  //  Serial.println("");
  //  int data1=root["data1"];
  //  Serial.print(data1);
  //  Serial.print("   Data 2 ");
  //  int data2=root["data2"];
  //  Serial.print(data2);
  //  Serial.println("");
  //  Serial.println("---------------------xxxxx--------------------");
  //
  if (s.available()) {
    StaticJsonBuffer<1000> json;
    JsonObject& root = json.parseObject(s);
    String state = root["state"];
    Serial.println(state);
//    if (state == 1){
//      digitalWrite(in3, HIGH);
//      digitalWrite(in4, LOW);
//      analogWrite(motor, motor_speed);
//    }
//    else {
//      digitalWrite(in3, LOW);
//      digitalWrite(in4, HIGH);
//      analogWrite(motor, motor_speed);
//    }
  }
}
