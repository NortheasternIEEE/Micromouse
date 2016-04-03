
#include "Drive.h"
#include "Sensors.h"

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  delay(5); //make sure it's initialized out of phase as the PID timer
  driveInit();
 
  drive(0.6, 0);
  delay(2000);
  brake();
  
}

void loop() {
  //Empty
}


