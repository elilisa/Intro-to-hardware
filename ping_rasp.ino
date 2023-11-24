#include <WiFi.h>

#include <ESP32Ping.h>  

const char* ssid = "NetworkName"; 

const char* password ="NetworkPassword"; 

void setup() {

  Serial.begin(115200);  

  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED) {

  delay(500);

  Serial.println("Connecting to WiFi...");

 }

 bool success = Ping.ping("RaspberryPi IP depends on the network", 3);  

 if(!success){

  Serial.println("Ping failed");

  return;

 }

 Serial.println("Ping successful.");

}

void loop() { }