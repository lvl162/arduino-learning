#include "DHT.h"  
#include "OneButton.h"   
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);   
#define BUTTON_PIN 4

OneButton button = OneButton(
  BUTTON_PIN,  // Input pin for the button
  false,       // Button is active high
  false        // Disable internal pull-up resistor
);

 
const int DHTPIN = A0;      
const int DHTTYPE = DHT11;  

int isF = 0;
int isTurnOff = 0;

DHT dht(DHTPIN, DHTTYPE);
float t,h,t_f;
void setup() {
  Serial.begin(9600);
  dht.begin();       
  analogWrite(6,80);
  lcd.begin();
  lcd.clear(); 
  button.attachDoubleClick(doubleclick);            
  button.attachClick(singleclick);                 
  button.attachLongPressStop(singleclick);           

}

void loop() {
  
  h = dht.readHumidity();    
  t = dht.readTemperature(); 
  t_f = t*1.8 + 32;
  button.tick(); 
  if (!isTurnOff) {
    lcd.backlight();
  lcd.setCursor(0,0);
  if (isF) {
  lcd.print("NhietDo(F): " + String(t_f));
 
  }
  else {
    lcd.print("NhietDo(C): " + String(t));
  }
  }
  else {
    lcd.clear();
    lcd.noBacklight();
    }
  delay(10);                     
}

void doubleclick() {   
  isTurnOff = !isTurnOff;                             
 Serial.println("double click");
} 
 
void singleclick(){   
  isF = !isF;                         
  Serial.println("single click");
}
