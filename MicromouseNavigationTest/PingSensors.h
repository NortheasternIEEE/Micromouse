#ifndef PINGSENSORS_H_
#define PINGSENSORS_H_

#include "Arduino.h"
#include "PID.h"
#include "Utility.h"
#include "Sensors.h"

#define frontSensorPin A4
#define backSensorPin A3

void pingFrontSensor(void);
void pingBackSensor(void);

#endif
