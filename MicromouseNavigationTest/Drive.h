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

#define DRIVE_KP        0.0005//0.001//1
#define DRIVE_KI        0.04//0.02
#define DRIVE_KD        0.05//0.075//2
#define DRIVE_MIN       -0.65//-1
#define DRIVE_MAX       0.65//1

#define TURN_KP         0.0007//0.0007  //0.0006
#define TURN_KI         0.65   //0.55
#define TURN_KD         0.02 //0.0175
#define TURN_MIN        -0.65
#define TURN_MAX        0.65

#define LATERAL_ADJUSTMENT_KP   0.5
#define LATERAL_ADJUSTMENT_KI   0.09//0.075
#define LATERAL_ADJUSTMENT_KD   0.075//0.035
#define LATERAL_ADJUSTMENT_MIN  -30
#define LATERAL_ADJUSTMENT_MAX  30

#define DRIVE_CORRECT_KP  0.0002//0.000025
#define DRIVE_CORRECT_KI  0.65//0.525
#define DRIVE_CORRECT_KD  0.03//0.025//0.055
#define DRIVE_CORRECT_MAX 0.575
#define DRIVE_CORRECT_MIN -0.575

#define DISTANCE_STOP_THRESHOLD 55 //make it a little bigger than the budge stop threshold to account for moving at high speeds
#define BUDGE_STOP_THRESHOLD    40
#define TURN_BEGIN_THRESHOLD    110
#define DRIVE_LOOP_DELAY        70

#define ANALOG_STOP_THRESHOLD  140

#define LR_COUNTS 4

#define SKETCHY_ADJUSTMENT_FORMULA(x) 0.00299401*(17949-sqrt(3.2399*pow(10,8)-6.68*pow(10,6)*x))

void driveInit(void);

void brake(void);
void hardBrake(uint8_t);

#define HARD_BRAKE_TIME_06    75
#define HARD_BRAKE_TIME_0525  75

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
