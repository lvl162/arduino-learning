#include "Servo.h"

// for Arduino microcontroller
//int servo_pin = 9;  
//int potpin = 0;

// for ESP8266 microcontroller
int servo_pin = D7;
int potpin = A0;

// for ESP32 microcontroller
//int servo_pin = 4;
//int potpin = 0;
 
Servo myservo;
int val;
 
void setup() {
  myservo.attach(servo_pin);
  Serial.begin(9600);
}
 
void loop() {
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  Serial.println(val);
  myservo.write(val);
  delay(300);
}
