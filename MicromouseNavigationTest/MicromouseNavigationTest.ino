#include "Drive.h"
#include "Sensors.h"

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  driveInit();


  float res;
  drive(0.55, 0);
  
}

void loop() {
  //Empty
}


