#include "Drive.h"
#include "Sensors.h"

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  driveInit();

  //getFrontDistance();
  //delay(100);

  turn(90);
  while(isTurning());
  
  turn(90);
  while(isTurning());
  digitalWrite(13, HIGH);
}

void loop() {
  /*
  if(getFrontDistance() > 120)
  {
    digitalWrite(13, LOW);
    driveDistance(18, 0.525);
    driveCorrect();
  }
  else
  {
    turn(-90);
    while(isTurning());
  }
  
  delay(100);
  */
  
}


