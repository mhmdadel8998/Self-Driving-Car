#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(6,12);

#define echoR 8 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigR 9 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoL 10 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigL 11//attach pin D3 Arduino to pin Trig of HC-SR04


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<SoftwareSerial.h>
#include <SPI.h>
SoftwareSerial s(3,1);

const char* ssid = "Adel";
const char* password = "12345678";
 


const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

int ML1=2;
int ML2=3;
int MR2=4;
int MR1=5;
int vel = 255; //Speed of motors (0-255) 
int flutter_out = 0; // start stopped 

long duration; // variable for the duration of sound wave travel
int distance;


void setup() { 
Serial.begin(9600); // initiates the serial port for communication with Bluetooth
  ArduinoUno.begin(4800);
pinMode(MR1,OUTPUT);
pinMode(MR2,OUTPUT);
pinMode(ML1,OUTPUT);
pinMode(ML2,OUTPUT);
pinMode(trigR, OUTPUT); // Sets the right trigPin as an OUTPUT
pinMode(echoR, INPUT); // Sets the right echoPin as an INPUT
pinMode(trigL, OUTPUT); // Sets the left trigPin as an OUTPUT
pinMode(echoL, INPUT); // Sets the left echoPin as an INPUT


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
int forward (){
    digitalWrite (ML1,HIGH);
    digitalWrite (ML2,LOW);
    digitalWrite (MR1,HIGH);
    digitalWrite (MR2,LOW);
    }
int stopmotors (){
    digitalWrite (ML1,LOW);
    digitalWrite (ML2,LOW);
    digitalWrite (MR1,LOW);
    digitalWrite (MR2,LOW);
    }
int turnL (){
    digitalWrite (ML1,LOW);
    digitalWrite (ML2,HIGH);
    digitalWrite (MR1,HIGH);
    digitalWrite (MR2,LOW);
    }

int turnR (){    
    digitalWrite (ML1,HIGH);
    digitalWrite (ML2,LOW);
    digitalWrite (MR1,LOW);
    digitalWrite (MR2,HIGH); 
    }
int ultrasonicL(){
  // Clears the trigPin condition
  digitalWrite(trigL, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoL, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance left: ");
  Serial.print(distance);
  Serial.println(" cm");
  }


int ultrasonicR(){
  // Clears the trigPin condition
  digitalWrite(trigR, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoR, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance right: ");
  Serial.print(distance);
  Serial.println(" cm");
  }


void loop() { 
ultrasonicL();
ultrasonicR();
delay(500);
if(Serial.available()>0){ // read bluetooth and store in state
flutter_out = Serial.read();
}
if(flutter_out=='1'){ // Forward
  Serial.println(flutter_out);
  forward();
  

}
if(flutter_out=='2'){ // right
    Serial.println(flutter_out);
     turnR();
     

}
if(flutter_out=='3'){ // Stop
    Serial.println(flutter_out);
    stopmotors();


}
if(flutter_out=='4'){ // left
    Serial.println(flutter_out);
     turnL();

} 
  








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
  
//  while(ArduinoUno.available()>0){
//  float val = ArduinoUno.parseFloat();
//  if(ArduinoUno.read()== '\n'){
//  Serial.println(val);
//  if(val==1.00){ // left
//    Serial.println("val=");
//    Serial.println(val);
//     forward();
//
//} 
//  }
//}

}
