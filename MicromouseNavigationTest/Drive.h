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

#define HORIZONTAL_ADJUSTMENT_COEFFICIENT 0.00025

#define DRIVE_KP  1
#define DRIVE_KI  0.02
#define DRIVE_KD  2
#define DRIVE_MIN -1
#define DRIVE_MAX 1

#define TURN_KP   0.005
#define TURN_KI   0.575
#define TURN_KD   0.1
#define TURN_MIN  -0.65
#define TURN_MAX  0.65

void driveInit(void);

void brake(void);
void hardBrake(void);

void turn(float);
uint8_t isTurning(void);

void drive(float, float);
uint8_t isDriving(void);



#endif
