#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Servo.h"

// WiFi network
//const char* ssid     = "Bitco";
//const char* password = "0905931912";

const char* ssid     = "Han";
const char* password = "12345678";

ESP8266WebServer server ( 80 );
Servo myservo;

int servo_pin = D7;
const int In3 = 2;
const int In4 = 0;
uint8_t Sp = 4;

char htmlResponse[3000];

void handleRoot() {

  snprintf ( htmlResponse, 3000,
             "<!DOCTYPE html>\
<html lang=\"en\">\
  <head>\
    <meta charset=\"utf-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  </head>\
  <body>\
          <h1>Time</h1>\
          <input type='text' name='date_hh' id='date_hh' size=2 autofocus> hh \
          <input type='text' name='date_mm' id='date_mm' size=2 autofocus> mm \
          <input type='text' name='date_ss' id='date_ss' size=2 autofocus> ss \
          <div>\
          <br><button id=\"save_button\">Save</button>\
          </div>\
    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\
    <script>\
      var hh;\
      var mm;\
      var ss;\
      $('#save_button').click(function(e){\
        e.preventDefault();\
        hh = $('#date_hh').val();\
        mm = $('#date_mm').val();\
        ss = $('#date_ss').val();\
        $.get('/save?hh=' + hh + '&mm=' + mm + '&ss=' + ss, function(data){\
          console.log(data);\
        });\
      });\
    </script>\
  </body>\
</html>");

  server.send ( 200, "text/html", htmlResponse );

}
void handleServo() {

  snprintf ( htmlResponse, 3000,
             "<!DOCTYPE html>\
<html lang=\"en\">\
  <head>\
    <meta charset=\"utf-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  </head>\
  <body>\
          <h1>Dien goc tu 0 - 180</h1>\
          <input type='text' name='goc' id='goc' size=2 autofocus> hh \
          <div>\
          <br><button id=\"goc_button\">OK</button>\
          </div>\
    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\
    <script>\
      var angle;\
        $('#goc_button').click(function(e){\
        e.preventDefault();\
        angle = $('#goc').val();\
        $.get('/angle?goc=' + angle, function(data){\
          console.log(data);\
        });\
      });\
    </script>\
  </body>\
</html>");

  server.send ( 200, "text/html", htmlResponse );

}
void handleDCMotor() {

  snprintf ( htmlResponse, 3000,
             "<!DOCTYPE html>\
<html lang=\"en\">\
  <head>\
    <meta charset=\"utf-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  </head>\
  <body>\
          <h1>Dien toc do 0 - 180</h1>\
          <input type='text' name='goc' id='goc' size=2 autofocus> hh \
          <div>\
          <br><button id=\"goc_button\">OK</button>\
          </div>\
    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\
    <script>\
      var angle;\
        $('#goc_button').click(function(e){\
        e.preventDefault();\
        angle = $('#goc').val();\
        $.get('/speed?s=' + angle, function(data){\
          console.log(data);\
        });\
      });\
    </script>\
  </body>\
</html>");

  server.send ( 200, "text/html", htmlResponse );

}
void handleAngle() {

  if (server.arg("goc") != "") {
    Serial.println("Goc: " + server.arg("goc"));
    int goc = ((String)server.arg("goc")).toInt();
    //  if (goc > 120) {
    //    digitalWrite(LED_BUILTIN, HIGH);
    //    Serial.println("Led on");
    //    }
    //  else {digitalWrite(LED_BUILTIN, LOW);
    //  Serial.println("Led off");}
    myservo.write(goc);
  }

}


void xmlRequest() {
  snprintf ( htmlResponse, 3000,
             "<!DOCTYPE html>\
<html lang=\"en\">\
  <head>\
    <meta charset=\"utf-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  </head>\
  <body>\
          <h1>Dien toc do 0 - 180</h1>\
          <input type='text' name='goc' id='goc' size=2 autofocus> hh \
          <div>\
          <br><button id=\"goc_button\">OK</button>\
          </div>\
    <script>\
      document.getElementById('goc_button').onclick = function() {\
        var xmlHttp = new XMLHttpRequest();\
        var angle = document.getElementById('goc').value;\
    xmlHttp.open( \"GET\", '/speed?s=' + angle, true ); \
    xmlHttp.send( null );\
        };\
    </script>\
  </body>\
</html>");

  server.send ( 200, "text/html", htmlResponse );
}
void handleSpeed() {

  if (server.arg("s") != "") {
    Serial.println("Speed: " + server.arg("s"));
    int speed = ((String)server.arg("s")).toInt();
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(Sp, speed);
    delay(200);
  }
}
void handleSave() {
  if (server.arg("hh") != "") {
    Serial.println("Hours: " + server.arg("hh"));
  }

  if (server.arg("mm") != "") {
    Serial.println("Minutes: " + server.arg("mm"));
  }

  if (server.arg("ss") != "") {
    Serial.println("Seconds: " + server.arg("ss"));
  }

}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  // Start serial
  Serial.begin(115200);
  delay(10);
  myservo.attach(servo_pin);
  // Connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on ( "/", handleRoot );
  server.on ("/save", handleSave);
  server.on("/servo", handleServo);
  server.on("/angle", handleAngle);
  server.on("/dcmotor", handleDCMotor);
  server.on("/speed", handleSpeed);
  server.on("/xml", xmlRequest);
  server.begin();
  Serial.println ( "HTTP server started" );


}

void loop() {
  server.handleClient();
}
