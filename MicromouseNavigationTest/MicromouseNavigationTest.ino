
#include "Drive.h"
#include "Sensors.h"
#include "PingSensors.h"

void setup() {

  Serial.begin(9600);
  /*pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  delay(5); //make sure it's initialized out of phase as the PID timer
  driveInit();
 
  drive(0.6, 0);
  delay(2000);
  brake();*/
  pinMode(14, OUTPUT);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}

void loop() {
  //pingFrontSensor();
  digitalWrite(14, HIGH);
  pingBackSensor();
  delay(100);
  pingFrontSensor();
}


