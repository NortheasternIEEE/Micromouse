#ifndef UTILITY_H_
#define UTILITY_H_

#include "Arduino.h"

void configureTimer(Tcc*, IRQn_Type, uint16_t);
float floatMap(float, float, float, float, float);

#endif


