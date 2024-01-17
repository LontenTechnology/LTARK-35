#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define IN_1  0            // L9110S A-1A motors Left       GPIO0 (D8)
#define IN_2  4            // L9110S A-1B motors Left       GPIO4 (D4)
#define IN_3  13           // L9110S B-1A motors Right      GPIO13(D7)
#define IN_4  12           // L9110S B-2A motors Right      GPIO12(D6)

String command;             //String to store app command state.
int speedCar = 200;         // 0~255.
int speed_low = speedCar/1.5;

const char* ssid = "lrobruya ESP8266 Car"; //wifi Hotspot Name
ESP8266WebServer server(80);
void setup() { 
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 
  Serial.begin(115200);
  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.print(myIP);
 
  // Starting WEB-server 
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();    
}

void Forward(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar+10);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void Backward(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}

void TurnLeft(){
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void TurnRight(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}

void goAheadLeft(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speed_low);
  analogWrite(IN_3, speedCar);
  digitalWrite(IN_4, LOW);
}

void goAheadRight(){
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, speedCar);
  analogWrite(IN_3, speed_low);
  digitalWrite(IN_4, LOW);
}

void goBackLeft(){ 
  analogWrite(IN_1, speed_low);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speedCar);
}

void goBackRight(){ 
  analogWrite(IN_1, speedCar);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, speed_low);
}

void Stop(){  
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void loop() {
  server.handleClient();
  command = server.arg("State");
  if (command == "F") Forward();
  else if (command == "B") Backward();
  else if (command == "L") TurnLeft();
  else if (command == "R") TurnRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "S") Stop();
  else speedCar = atoi(command.c_str());//Convert string type to integer
}

void HTTP_handleRoot(void) {
  if( server.hasArg("State") ){
    Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
