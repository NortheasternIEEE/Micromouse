#ifndef UTILITY_H_
#define UTILITY_H_

#include "Arduino.h"

#define signum(x) ((x >= 0) ? 1 : -1)

void configureTimer(Tcc*, IRQn_Type, uint16_t);
float floatMap(float, float, float, float, float);


#endif


