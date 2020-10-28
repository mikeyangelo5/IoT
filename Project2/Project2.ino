#include "DHT.h"  //import DHT library
const int pinDHT = 0;
const int pinButton = 4;
const int pinLEDR = 23;
const int pinLEDY = 27;
const int pinLEDG = 26;
#define DHTTYPE DHT11 //definisikan tipe DHT yang kita gunakan (DHT11/DHT22)
DHT dht(pinDHT, DHTTYPE);
int buttonState = 0;
boolean statusStart = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinButton, INPUT);
  pinMode(pinLEDR, OUTPUT);
  pinMode(pinLEDY, OUTPUT);
  pinMode(pinLEDG, OUTPUT);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  buttonState = digitalRead(pinButton);
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if(buttonState == HIGH) {
    statusStart = !statusStart;
  }
  if(statusStart==1){
    if(temperature<35) {
      digitalWrite(pinLEDR, LOW);
      digitalWrite(pinLEDY, LOW);
      digitalWrite(pinLEDG, HIGH);
    } else if (temperature>=35 && temperature<=50) {
      digitalWrite(pinLEDR, LOW);
      digitalWrite(pinLEDY, HIGH);
      digitalWrite(pinLEDG, HIGH);
    } else if (temperature>50) {
      digitalWrite(pinLEDR, HIGH);
      digitalWrite(pinLEDY, HIGH);
      digitalWrite(pinLEDG, HIGH);
    }
    Serial.print(temperature);
    Serial.println(F("°C "));
  } else {
    digitalWrite(pinLEDR, LOW);
    digitalWrite(pinLEDY, LOW);
    digitalWrite(pinLEDG, LOW); 
  }
}
