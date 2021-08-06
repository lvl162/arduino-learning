// D5 D6 node -> 10 11 Uno thong qua tro
// GND node -> GND Uno

#include<ESP8266WiFi.h>
#include<ESPAsyncTCP.h>
#include<ESPAsyncWebServer.h>
#include<SoftwareSerial.h>
#include<ArduinoJson.h>
SoftwareSerial s(D6, D5);
const char* ssid =  "ESP";
const char* password = "12345678";
String input = "";
bool state = 0;
AsyncWebServer server(80);
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=W">
    <title>ESP8266</title>
</head>
<body>
    <form action="/dc" method="get">
        <label for="">goc_quay</label>
        
        <br>
        <br>
        <input type="submit" value="submit">
    </form>
</body>
</html>
)rawliteral";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  s.begin(9600);
  
//  WiFi.softAP(ssid, password);
//
//  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send_P(200, "text/html", index_html);
//    });
//   server.on("/dc", HTTP_GET, [](AsyncWebServerRequest *request){
////    String goc = request->getParam("goc")->value();
//    state = !state;
//    StaticJsonBuffer<1000> json;
//    JsonObject& root = json.createObject();
//    root["state"] = "123";
//    root.printTo(s);
//   
//    request->send_P(200, "text/html", index_html);
//    });
//    server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  StaticJsonBuffer<1000> json;
    JsonObject& root = json.createObject();
    root["state"] = "1234";
    root.printTo(s);
    delay(1000);
}
