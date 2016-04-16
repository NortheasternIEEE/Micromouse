#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// Note: We commented out the error in the header file regarding the ADR pin being set to high
// We did not actually change the pin to High so if we have errors it might be the cause

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

float xAngle;
float initAbsVal;

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
  sensors_event_t event;
  bno.getEvent(&event);
  initAbsVal = (float)event.orientation.x;
  Serial.print("Initial Absolute Gyro Value"); Serial.println((float)event.orientation.x);
  Serial.print("Adjust value"); Serial.println(initAbsVal);
  }

  // return relative angle
float findAngle() {
  sensors_event_t event;
  bno.getEvent(&event);
  if (((float)event.orientation.x - initAbsVal) < 0)
  {
    return (float)event.orientation.x - initAbsVal + 360;
  }
  else
  {
    return (float)event.orientation.x - initAbsVal;
  }
}



void loop() {
  // if oriented forward in the bottom left corner, 0 should be up, 90 should be right, 180 should be down, 270 should be left
  xAngle = findAngle();
  if ((xAngle >= 85) && (xAngle <= 95))
  {
    Serial.print("Right");
  }
  else if ((xAngle >= 175) && (xAngle <= 185))
  {
    Serial.print("Back");
  }
  else if ((xAngle >= 265) && (xAngle <= 275))
  {
    Serial.print("Left");
  }
  else if ((xAngle >= 355) || (xAngle <= 5))
  {
    Serial.print("Forward");
  }
  delay(100);
}

