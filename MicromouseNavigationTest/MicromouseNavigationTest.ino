#include "Drive.h"
#include "Sensors.h"

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  delay(5); //make sure it's initialized out of phase as the PID timer
  driveInit();


  float res;
  drive(0.55, 0);
  while(getPosition() < 18) {
     Serial.println(getPosition());
     delay(50);
  }
  brake();
}

void loop() {
  //Empty
}


