/*          MOSI  MISO  SCK CS
  Arduino Uno 11    12    13  10*/
#include <SPI.h>
#include <SD.h>
#include "DHT.h"
#include <TimeLib.h>

File myFile;
const int DHTPIN = A0;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
float t = 0, h = 0, t_f;

// change this to match your SD shield or module;
const int chipSelect = 10;

void setup()
{
  // Open serial communications and wait for port to open:
  dht.begin();
  Serial.begin(9600);

  
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
  SD.remove("log.txt");
  SD.remove("log1.txt");
  
}
void WriteWithoutChanges() {
  time_t time = now();

  
  h = dht.readHumidity();
  t = dht.readTemperature();

  myFile = SD.open("log.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
      
//    String log = "NhietDo: " + String(t) + "\nDoAm: " + String(h) + "\n\n";
      String log = String(hour(time)) + ":" + String(minute(time)) + ":" + String(second(time)) + " Nhiet Do: " + String(t) + "\n Do Am: " + String(h) + "\n\n";
    Serial.print(log);
    myFile.println(log);
    // close the file:
    myFile.close();
    Serial.println("...done.");
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  delay(2000);
}
void loop()
{
  time_t time = now();

//  WriteWithoutChanges();
  float h_temp = dht.readHumidity();
  float t_temp = dht.readTemperature();



  myFile = SD.open("log1.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    if (h_temp != h || t_temp != t) {
      h = h_temp;
      t = t_temp;
      
//      String log = "NhietDo: " + String(t) + "C\nDoAm: " + String(h) + "%\n\n";
      String log = String(hour(time)) + ":" + String(minute(time)) + ":" + String(second(time)) + " Nhiet Do: " + String(t) + "\n Do Am: " + String(h) + "\n\n";
      Serial.print(log);
      myFile.println(log);
      Serial.println("...done.");
      // close the file:
    }
    else {
      Serial.println("Still not changing");
    }
    myFile.close();

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  delay(1000);
}
