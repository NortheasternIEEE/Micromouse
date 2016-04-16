
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <VL6180X.h>

#include "Sensors.h"

void sensorsInit() {

  Wire.begin();
  
  orientationInit();
  encodersInit();
  distanceInit();
}


//-------- ORIENTATION --------//

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void orientationInit(void);

void orientationInit() {
  if (!bno.begin()) {
    //Serial.print("No BNO055 detected");
    while(1) {
      digitalWrite(13, HIGH);
    }
  }
}

void getOrientation(float* x, float* y, float* z) {
  sensors_event_t event;
  bno.getEvent(&event);
  *x = event.orientation.x;
  *y = event.orientation.y;
  *z = event.orientation.z;
}


//-------- ENCODERS --------//
void encodersInit(void);

void encodersInit() {
  //Now, initialize encoders
  //Only use 1X decoding
  pinMode(LEFT_ENCODER_CLK, OUTPUT);
  pinMode(LEFT_ENCODER_MISO, INPUT);
  pinMode(RIGHT_ENCODER_CLK, OUTPUT);
  pinMode(RIGHT_ENCODER_MISO, INPUT);
}

uint32_t getLeftEncoder() {
  uint32_t ticks = 0;
  for(int i=0; i<32; i++) {
    digitalWrite(LEFT_ENCODER_CLK, HIGH);
    delayMicroseconds(65);
    digitalWrite(LEFT_ENCODER_CLK, LOW);
    delayMicroseconds(65);
    if(digitalRead(LEFT_ENCODER_MISO)) {
      ticks |= (1 << i);
    }
  }
  return ticks;
}

uint32_t getRightEncoder() {
  uint32_t ticks = 0;
  for(int i=0; i<32; i++) {
    digitalWrite(RIGHT_ENCODER_CLK, HIGH);
    delayMicroseconds(65);
    digitalWrite(RIGHT_ENCODER_CLK, LOW);
    delayMicroseconds(65);
    if(digitalRead(RIGHT_ENCODER_MISO)) {
      ticks |= (1 << i);
    }
  }
  return ticks;
}

//in cm
float getPosition() {
  return (((getLeftEncoder()+getRightEncoder())/2.0)/TICKS_IN_ONE_REVOLUTION) * WHEEL_CIRCUMFERENCE;
}

//-------- DISTANCE SENSORS --------//

VL6180X rightSensor;
VL6180X leftSensor;

void distanceInit(void);
float microsecondsToCentimeters(float);

void distanceInit() {
  //Front and Back Distance Sensors
  pinMode(FRONT_DISTANCE_SENSOR, INPUT);
  pinMode(BACK_DISTANCE_SENSOR, INPUT);

  //Left and Right Distance Sensors
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

  //Turn on PING supply
  pinMode(PING_POWER, OUTPUT);
  digitalWrite(PING_POWER, HIGH);
}

uint8_t getLeftDistance() {
  return leftSensor.readRangeSingle()+LEFT_DISTANCE_OFFSET;
}

uint8_t getRightDistance() {
  return rightSensor.readRangeSingle();
}

float getFrontDistance(void) {
  pinMode(FRONT_DISTANCE_SENSOR, OUTPUT);
  digitalWrite(FRONT_DISTANCE_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(FRONT_DISTANCE_SENSOR, HIGH);
  delayMicroseconds(5);
  digitalWrite(FRONT_DISTANCE_SENSOR, LOW);

  pinMode(FRONT_DISTANCE_SENSOR, INPUT);
  float duration = pulseIn(FRONT_DISTANCE_SENSOR, HIGH);
  float cm = microsecondsToCentimeters(duration);
  return cm*10;
}

float getBackDistance(void) {
  pinMode(BACK_DISTANCE_SENSOR, OUTPUT);
  digitalWrite(BACK_DISTANCE_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(BACK_DISTANCE_SENSOR, HIGH);
  delayMicroseconds(5);
  digitalWrite(BACK_DISTANCE_SENSOR, LOW);

  pinMode(BACK_DISTANCE_SENSOR, INPUT);
  float duration = pulseIn(BACK_DISTANCE_SENSOR, HIGH);
  float cm = microsecondsToCentimeters(duration);
  return cm*10;
}

float microsecondsToCentimeters(float microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

  

