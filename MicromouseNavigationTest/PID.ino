#include "PID.h"

void pid_sat_init(pid_sat_t* pid, float Kp, float Ki, float Kd, float outputMin, float outputMax) {
  pid->Kp = Kp;
  pid->Ki = Ki;
  pid->Kd = Kd;
  pid->outputSaturationMin = outputMin;
  pid->outputSaturationMax = outputMax;
}

void pid_sat_set_setpoint(pid_sat_t* pid, float setpoint) {
  pid->setpoint = setpoint;
}

//PID, location, setPoint -> PID output 
float pid_sat_update(pid_sat_t* pid, float process) {
  //First, calculate error
  float error = process - pid->setpoint;
  
  //Calculate proportional term
  float p = pid->Kp * error;
  
  //Calculate integral term and update accumulator
  pid->accumulation += error;
  //saturate the integral
  pid->accumulation = constrain(pid->accumulation, pid->outputSaturationMin, pid->outputSaturationMax);
  float i = pid->Ki * pid->accumulation;
  

  //Calculate derivative term and update previous error
  float d = pid->Kd * (error - pid->previousError);
  pid->previousError = error;

  //Calculate output value
  float output = p+i+d;
  
  return constrain(output, pid->outputSaturationMin, pid->outputSaturationMax);
}

void pid_sat_reset(pid_sat_t* pid) {
  pid->accumulation = 0;
  pid->previousError = 0;
}

