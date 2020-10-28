//Get GPIO Number to Const
const int pinLEDR = 23;
const int pinLEDY = 27;
const int pinLEDG = 26;

//Set all LED state to LOW
int RState = LOW;
int YState = LOW;
int GState = LOW;

//Variables for Save Time and Interval Time in LED
long SavedTime = 0;
long IntervalTime = 10000;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLEDR, OUTPUT);
  pinMode(pinLEDY, OUTPUT);
  pinMode(pinLEDG, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long TimeNow = millis();
  unsigned long ElapsedTime = TimeNow - SavedTime;
  if(ElapsedTime > IntervalTime){
    SavedTime = TimeNow;
  }
  if(ElapsedTime < 4000) {
    RState = HIGH;
    YState = LOW;
    GState = LOW;
  }
  if(ElapsedTime > 4000 && ElapsedTime < 8000) {
    RState = LOW;
    YState = LOW;
    GState = HIGH;
  }
  if(ElapsedTime > 8000) {
    RState = LOW;
    YState = HIGH;
    GState = LOW;
  }
  digitalWrite(pinLEDR, RState);
  digitalWrite(pinLEDY, YState);
  digitalWrite(pinLEDG, GState);
}
