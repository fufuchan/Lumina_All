#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int outPin = 7;
const int inPin = 2;
int pinVal = 0;
int lastPinVal = 1;

const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;
const int led5 = 12;


void setup() {
  Serial.begin(115200);

  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (outPin, OUTPUT);
  pinMode(inPin, INPUT);

  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (led4, OUTPUT);
  pinMode (led5, OUTPUT);


  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    outputOn();
    NormalBehaviour();

    if (measure.RangeStatus != 4 && pinVal == 1) {
      CommunicatingWOne();
    }
  } else {
    Serial.println(" out of range ");
    outputOff();
    Off();
  }
  input();
  delay(100);
}

void outputOn () {
  digitalWrite(outPin, HIGH);
}

void outputOff() {
  digitalWrite(outPin, LOW);
}


void input () {
  pinVal = digitalRead(inPin);
  if (lastPinVal != pinVal) {
    digitalWrite(LED_BUILTIN, pinVal);
    //    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(pinVal);
    lastPinVal = pinVal;
  }
}

void NormalBehaviour() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);

}

void CommunicatingWOne() {
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led3, HIGH);
  delay(100);
  digitalWrite(led4, HIGH);
  delay(100);
  digitalWrite(led5, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
  delay(100);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led3, LOW);
  delay(100);
  digitalWrite(led4, LOW);
  delay(100);
  digitalWrite(led5, LOW);
  delay(100);
}

void Off() {

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(20);
}


