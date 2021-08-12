/*
 Pin  | Wiring to Arduino Uno
SDA   | Digital 10
SCK   | Digital 13
MOSI  | Digital 11
MISO  | Digital 12
IRQ   | unconnected
GND   | GND
RST   | Digital 9
3.3V  | 3.3V
 */
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int isLedOn = 0;
// FSM params 
int _state = 0; // starting with state 0: waiting for button to be pressed
unsigned long _startTime; // will be set in state 1

const int ButtonDown = 1, ButtonUp= 0;
const long _pressTicks = 5000, _clickTicks = 2000;

void _pressFunc(){
  digitalWrite(7,1);
  Serial.println("press");
  }
void _clickFunc(){
  Serial.println("1click");
  digitalWrite(7,1);
  };
void _doubleClickFunc(){
  digitalWrite(7,0);
  Serial.println("2click");
  };

//--------

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(7, OUTPUT);

}

int readCard(String UID = "55 FD 46 2A") {

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    if ( ! mfrc522.PICC_IsNewCardPresent())
//    Serial.println("K co");
    return 0;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
//    Serial.println("K doc dc");
    return 0;
  }
  //Show UID on serial monitor
//  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
//  Serial.println();
//  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == UID) //change here the UID of the card/cards that you want to give access
  {
//    Serial.println("Authorized access");
//    Serial.println();
//    digitalWrite(7, 1);
    return 1;
//    delay(3000);
  }
 
 else   {
//    Serial.println(" Access denied");
//    delay(3000);
//      digitalWrite(7, 0);
      return 0;
  }
  
  }

void loop() 
{
  int buttonLevel = readCard(); // current button signal.
//  Serial.println(buttonLevel);
  unsigned long now = millis(); // current (relative) time in msecs.
  if (_state == 0) { // waiting for One pin being pressed.
  if (buttonLevel == ButtonDown) {
    _state = 1; // step to state 1
    _startTime = now; // remember starting time
  } // if
  } else if (_state == 1) { // waiting for One pin being released.
  if (buttonLevel == ButtonUp) {
    _state = 2; // step to state 2

  } else if ((buttonLevel == ButtonDown) && (now > _startTime + _pressTicks)) {
    if (_pressFunc) _pressFunc();
    _state = 6; // step to state 6
  } // if
  } else if (_state == 2) { // waiting for One pin being pressed the second time or timeout.
  if (now > _startTime + _clickTicks) {
    // this was only a single short click
    if (_clickFunc) _clickFunc();
    _state = 0; // restart.

  } else if (buttonLevel == ButtonDown) {
    _state = 3; // step to state 3
  } // if
  } else if (_state == 3) { // waiting for One pin being released finally.
  if (buttonLevel == ButtonUp) {
    // this was a 2 click sequence.
    if (_doubleClickFunc) _doubleClickFunc();
    _state = 0; // restart.
  } // if
  } else if (_state == 6) { // waiting for One pin being release after long press.
  if (buttonLevel == ButtonUp) {
    _state = 0; // restart.
  } // if
}

  delay(10);
} 


boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}