#include "Drive.h"
#include "Sensors.h"

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  driveInit();

  driveDistance(18, 0.6);

  getFrontDistance();
  delay(100);
  /*
  turn(90);
  while(isTurning());
  
  turn(90);
  while(isTurning());
  digitalWrite(13, HIGH);
  */

  /*
  for(int i=0; i<5; i++) {
    //driveDistance(18, 0.525);
  }
  turn(-90);
  while(isTurning());
  driveDistance(18, 0.525);
  */
}

void loop() {
  /*
  if(getFrontDistance() > 120)
  {
    digitalWrite(13, LOW);
    driveDistance(17, 0.525);
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


