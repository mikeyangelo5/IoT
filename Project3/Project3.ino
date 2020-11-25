#include <ESP32Servo.h>
#include "WiFi.h"
#include <WiFiClient.h>
#include <MQTT.h>
#include "DHT.h"

#define DHTType DHT11

const int pinDHT = 4;
Servo myServo;
int pos = 00;

DHT dht(pinDHT, DHTType);

const char ssid[] = "3NUR2M";
const char pass[] = "micmar2720";

WiFiClient net;
MQTTClient client;

String espName = "ESP32";
String usernameBroker = "mpandu27";
String passwordBroker = "58cfb6f1f6420a9f";
unsigned long Millis = 0;
boolean Started = false;

void connect() {
  Serial.print("Checking WiFi Availability...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);  
  }
  Serial.print("\nConnecting...");
  while (!client.connect("ESP32", "mpandu27", "58cfb6f1f6420a9f")){
    Serial.print(".");
    delay(1000);
  }
  client.subscribe("/test");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming Message From " + topic + " : " + payload);
  if(payload == "1"){
    Started = true;
  } else {
    Started = false;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(25);
  dht.begin();
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  delay(10);
  if(!client.connected()){
    connect();
  }
  float Temp = dht.readTemperature();
  if(Started == true) {
    Serial.println(Temp);
    if(Temp < 30) {
      myServo.write(0);
    }
    if(Temp > 30) {
      myServo.write(180);
    }
  }
}
