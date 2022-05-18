#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<SoftwareSerial.h>
#include <SPI.h>
SoftwareSerial s(3,1);

const char* ssid = "YMED";
const char* password = "12345678";
 
void setup () {
  s.begin(9600);
  Serial.begin(9600);
  SPI.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
  Serial.println("Connected to WiFi Network");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
            HTTPClient http;  //Declare an object of class HTTPClient
            WiFiClient client;
     http.begin(client,"http://192.168.1.4:8000/image");  //Specify request destination
     int httpCode = http.GET();     //Send the request
     if (httpCode > 0) { //Check the returning code
       String payload = http.getString(); //Get the request response payload
       Serial.println(payload);
//       char data='f';
         s.write(payload[0]); //connection bet esp & arduino
       //Serial.println(1);
        Serial.println(payload);
        delay(1000);
        Serial.println(payload[0]); 
     }
     delay(1500);
     http.end();
  
 
}