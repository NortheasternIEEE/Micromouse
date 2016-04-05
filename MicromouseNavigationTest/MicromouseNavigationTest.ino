#include "Drive.h"
#include "Sensors.h"

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  delay(5); //make sure it's initialized out of phase as the PID timer
  driveInit();
 
  drive(0.9, 0);
  long start = millis();
  while(millis()-start < 200);
  drive(0.4, 0);
  
}

void loop() {
  //Empty
}


