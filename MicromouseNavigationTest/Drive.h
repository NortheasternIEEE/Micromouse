#ifndef DRIVE_H_
#define DRIVE_H_

#define FORWARD   1
#define BACKWARD  -1

#include "Arduino.h"
#include "PID.h"
#include "Utility.h"
#include "Sensors.h"

#define LEFT_POWER    A1
#define LEFT_MOTOR_1  6
#define LEFT_MOTOR_2  9
#define RIGHT_POWER   A2
#define RIGHT_MOTOR_1 5
#define RIGHT_MOTOR_2 10

#define LATERAL_ADJUSTMENT_COEFFICIENT 0.0004

#define DRIVE_KP        1
#define DRIVE_KI        0.02
#define DRIVE_KD        2
#define DRIVE_MIN       -1
#define DRIVE_MAX       1

#define TURN_KP         0.0015  //0.0006
#define TURN_KI         0.525   //0.55
#define TURN_KD         0.03 //0.0175
#define TURN_MIN        -0.65
#define TURN_MAX        0.65
#define STOP_THRESHOLD  110

#define LR_COUNTS 4

void driveInit(void);

void brake(void);
void hardBrake(void);

//Turns the robot relative to its current angle
void turn(float);

//turn the robot to some absolute position
void turnAbsolute(float);
uint8_t isTurning(void);

//Drive the robot at a given speed indefinitely
void drive(float);

//Call this after manually stopping a drive to ensure that the robot is facing the direction we want
void driveCorrect(void);

//Drives the robot a given distance at a given speed
void driveDistance(float, float);

uint8_t isDriving(void);



#endif
