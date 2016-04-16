#ifndef PID_H_
#define PID_H_

#include "Arduino.h"

typedef struct {
  float Kp; //Proportional Gain
  float Ki; //Integral Gain
  float Kd; //Derivative Gain
  float outputSaturationMin; //Lower limit of output
  float outputSaturationMax; //Upper limit of output
  float setpoint; //Current setpoint
  float accumulation; //Integral term accumulator
  float previousError;  //Previous error
} pid_sat_t;

void pid_sat_init(pid_sat_t*, float, float, float, float, float);
void pid_sat_set_setpoint(pid_sat_t*, float);
float pid_sat_update(pid_sat_t*, float);
void pid_sat_reset(pid_sat_t*);

#endif
