#include <VL6180X.h>
#include <Wire.h>

#define LEFT_CE 11
#define NEW_RIGHT_ADDRESS 0x09

VL6180X rightSensor;
VL6180X leftSensor;

void setup() {
  
  // Initialize communications
  Serial.begin(9600);
  Wire.begin();

  // First, let's change the address of the right sensor
  pinMode(LEFT_CE, OUTPUT);
  digitalWrite(LEFT_CE, LOW); //Toggle the left sensor off
  rightSensor.setAddress(NEW_RIGHT_ADDRESS); // Set it to some new address
  pinMode(LEFT_CE, INPUT); // Turn it back on 
  
  // Now, we can configure both sensors normally
  leftSensor.init();
  rightSensor.init();
  leftSensor.configureDefault();
  rightSensor.configureDefault();
  
  leftSensor.setTimeout(500);
  rightSensor.setTimeout(500);

}

void loop() {
  int left = leftSensor.readRangeSingle();
  int right = rightSensor.readRangeSingle();

  Serial.print("Left: ");
  Serial.print(left-30);
  Serial.print("mm\t");
  Serial.print("Right: ");
  Serial.print(right-30);
  Serial.print("mm\t");
  Serial.println(left-right);

  delay(50);
}


