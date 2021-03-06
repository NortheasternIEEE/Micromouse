#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

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
  
  Serial.begin(115200);
  if (!bno.begin()) {
    Serial.print("No BNO055 detected");
    while(1);  
  }
  displaySensorDetails();
}



void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t event;
  bno.getEvent(&event);
  
  Serial.print("Orientation: ");
  Serial.print((float)event.orientation.x);
  Serial.print(" ");
  Serial.print((float)event.orientation.y);
  Serial.print(" ");
  Serial.print((float)event.orientation.z);
  Serial.print(" ");
  Serial.print("\n");

  delay(100);
}
