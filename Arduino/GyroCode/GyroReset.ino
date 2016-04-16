#include <Adafruit_Sensor.h>

#include <Adafruit_BNO055.h>

#include <Wire.h>
#include <utility/imumaths.h>
#include "Utility.h"

int ledPin = 13;

int sensorPinFront = A1;    // select the input for sensor
int sensorPinBack = A2;    // select the input for sensor
int sensorValueFront = 0;  // Stores Value from sensor
int sensorValueBack = 0;  // Stores Value from sensor

// example location for testing
location position;

// Note: We commented out the error in the header file regarding the ADR pin being set to high
// We did not actually change the pin to High so if we have errors it might be the cause

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (1)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
  
}

void setup() {
  
  Serial.begin(9600);
  if (!bno.begin()) {
    Serial.print("No BNO055 detected");
    while(1);  
  }
  pinMode(ledPin, OUTPUT); //CHANGE THIS NUMBER - We are not going to be using this LED pin
  displaySensorDetails();
  // position.x = 23;
  // position.y = 15;
  // Serial.println(position.x);
  // Serial.println(position.y);
  pinMode(sensorPinFront, INPUT);
  pinMode(sensorPinBack, INPUT);
  }

// resets location if angle greater than 45 deg
void ResetCrashed(location *loc) {
  sensors_event_t event;
  bno.getEvent(&event);

  // reset location if angle greater than 45 deg
  if (((float)event.orientation.z > 45) && (float)event.orientation.z < 315)
  {
    // reset location
    loc->x = 0;
    loc->y = 0;
    // Write to LED so we know its reset
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    // Otherwise turn the LED off
    digitalWrite(ledPin, LOW);
  }
}

// Determine when you are back at the start
int atStart() {
  while (1) {
    sensors_event_t event;
    bno.getEvent($event);

    //Are you below 10 degrees for your z axis, if so then ping the walls
    if (((float))event.orientation.z < 10 && (float)event.orientation.z > 350) {
        sensorValueBack = analogRead(sensorPinBack);
        if (sensorValueBack) {
          sensorValueBack = analogRead(sensorPinBack);
          if (sensorValueBack) {
            return 1;
          }
        }
        delay(100);
    }
    else {
      delay(100);
    }
  }
}

void loop(){
  ResetCrashed(&position);
  Serial.println(position.x);
  Serial.println(position.y);
  delay(100);
}

