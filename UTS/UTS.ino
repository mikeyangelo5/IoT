#define BLYNK_PRINT Serial

#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "cPhdV3qDGFkpEeXpbkY2mulHJN946bl5";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "3NUR2M";
char pass[] = "micmar2720";

#define DHTTYPE DHT11
const int pinLDR = 36;
const int pinDHT = 0;
int sliderLDRValue;
int sliderDHTValue;
WidgetLED ldrLEDG(V6);
WidgetLED ldrLEDR(V9);
WidgetLED dhtLEDG(V7);
WidgetLED dhtLEDR(V10);
DHT dht(pinDHT, DHTTYPE);
boolean Started = false;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(pinLDR, INPUT);
  dht.begin();

//  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,100,2), 8080);
}

void SendSensorsData() {
  int temperature = dht.readTemperature();
  float brightness = analogRead(pinLDR);
  if(isnan(temperature)) {
    Serial.println("Failed to read from DHT Sensors!");
    return;
  }
  if(isnan(brightness)) {
    Serial.println("Failed to read from LDR Sensors!");
    return;
  }
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V3, temperature);
  if(brightness < sliderLDRValue) {
    brightness = 0.009768*brightness+10;
    Blynk.virtualWrite(V0, brightness);
    Blynk.virtualWrite(V2, brightness);
    ldrLEDR.off();
    ldrLEDG.setValue(255);
  } else {
    brightness = 0.009768*brightness+10;
    Blynk.virtualWrite(V0, brightness);
    Blynk.virtualWrite(V2, brightness);
    ldrLEDG.off();
    ldrLEDR.setValue(255);
  }
  if(temperature <= sliderDHTValue) {
    dhtLEDR.off();
    dhtLEDG.setValue(255);
  } else {
    dhtLEDG.off();
    dhtLEDR.setValue(255);
  }
}

BLYNK_WRITE(V4) {
  sliderLDRValue = param.asInt();
}

BLYNK_WRITE(V5) {
  sliderDHTValue = param.asInt();
}

BLYNK_WRITE(V8) {
  Started = param.asInt();
}

void loop()
{
  Blynk.run();
  if(Started == HIGH) {
    SendSensorsData();
  } else {
    ldrLEDR.off();
    ldrLEDG.off();
    dhtLEDR.off();
    dhtLEDG.off();
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V2, 0);
  }
}
