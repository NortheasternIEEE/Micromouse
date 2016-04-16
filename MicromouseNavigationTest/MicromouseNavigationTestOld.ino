#include "Drive.h"
#include "Sensors.h"

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sensorsInit();
  driveInit();

  setLeftMotorDirection(FORWARD);
  setRightMotorDirection(FORWARD);
  //driveDistance(15.25, 0.575);
  //digitalWrite(13, LOW);
  //delay(1000);
  //setLeftMotorDirection(FORWARD);
  //setRightMotorDirection(FORWARD);
  //driveDistance(15.25, 0.575);
  //digitalWrite(13, HIGH);

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
  
  float front = 0;
  for(int i=0; i<5; i++) {
    front += getFrontDistance();
    delay(100);
  }
  front /= 5;
  if(front > TURN_BEGIN_THRESHOLD) {
    digitalWrite(13, LOW);
    setLeftMotorDirection(FORWARD);
    setRightMotorDirection(FORWARD);
    driveDistance(15.25, 0.565); //0.575 was changed -Charlie
    digitalWrite(13, HIGH);
  }
  else {
    delay(100);
    uint8_t doAnExtraBudge = 0;
    while(getFrontDistance() > BUDGE_STOP_THRESHOLD) {
      setLeftMotorDirection(FORWARD);
      setRightMotorDirection(FORWARD);
      driveDistance(0.75, 0.575);
      doAnExtraBudge = 1;
    }
    if(doAnExtraBudge) {
      setLeftMotorDirection(FORWARD);
      setRightMotorDirection(FORWARD);
      driveDistance(1, 0.575);
    }

    //now ping the sides to see which way we should turn
    float left = getLeftDistance();
    if(left < 100 && left > 10) {
      turn(-90);
      while(isTurning());
      driveCorrect();
    }
    turn(-90);
    while(isTurning());
    driveCorrect();

    /*
    //now after a turn, correct if we're too close
    if(fabs(getFrontDistance()-getBackDistance()) > 7.5) {
      //budge backwards
      setLeftMotorDirection(BACKWARD);
      setRightMotorDirection(BACKWARD);
      driveDistance(1, 0.525);
      driveCorrect();
    }
    */
  }
  
  //Serial.println(getFrontDistance());
  //Serial.print('\t');
  //Serial.println(getBackDistance());
  //float temp = getLeftDistance();  
  //Serial.println(temp);
  delay(100);
}


