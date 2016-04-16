#ifndef MicromousePIDTest_h
#define MicromousePIDTest_h

#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "PID.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define LEFT_POWER    A1
#define LEFT_MOTOR_1  6
#define LEFT_MOTOR_2  9
#define RIGHT_POWER   A2
#define RIGHT_MOTOR_1 5
#define RIGHT_MOTOR_2 10

#define BNO055_SAMPLERATE_DELAY_MS (1)

#define Y_SPEED 0.7 //80% speed

void arcadeDrive(float xPower, float yPower, float* leftOutput, float* rightOutput);

float floatMap(float x, float in_min, float in_max, float out_min, float out_max);

#endif /*MicromousePIDTest_h*/