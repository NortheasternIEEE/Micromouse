#include "Drive.h"
#include "Sensors.h"
#include "Utility.h"
#include "map.h"


#define NELEMS(x) (sizeof(x)/sizeof(x[0]))
struct node graph[mazeSize][mazeSize];
struct loc currentPoint;

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

  initializeGraph(graph);
  initializeLoc(&currentPoint);

  map(&currentPoint, graph);
}



void loop() {
 
}




