#include "Drive.h"

//This variable is used to determine when a turn or drive is complete.
//It measures how many consecutive times our PID output is zero.
//if it's zero fo a while, we know that the move is complete, and we can be done.
volatile uint8_t zeroCount = 0;
volatile float prevVal = 0;
volatile uint8_t driving = 0;
volatile uint8_t turning = 0;
volatile float driveSpeed = 0; //the y speed for driving

volatile pid_sat_t drive_pid;
volatile pid_sat_t turn_pid;

void setLeftMotorDirection(int8_t);
void setRightMotorDirection(int8_t);
void arcadeDrive(float, float, float*, float*);
void updatePID(float);
void updateDrivePID(float);
void updateTurnPID(float);

void driveInit() {
  pinMode(LEFT_POWER, OUTPUT);
  pinMode(LEFT_MOTOR_1, OUTPUT);
  pinMode(LEFT_MOTOR_2, OUTPUT);
  pinMode(RIGHT_POWER, OUTPUT);
  pinMode(RIGHT_MOTOR_1, OUTPUT);
  pinMode(RIGHT_MOTOR_2, OUTPUT);

  pid_sat_init((pid_sat_t*)&drive_pid, DRIVE_KP, DRIVE_KI, DRIVE_KD, DRIVE_MIN, DRIVE_MAX); //set gains and limits
  pid_sat_init((pid_sat_t*)&turn_pid, TURN_KP, TURN_KI, TURN_KD, TURN_MIN, TURN_MAX);

  configureTimer(TCC0, TCC0_IRQn, 1874); //configure to execute every 10ms
}

void setLeftMotorDirection(int8_t dir) {
  if(dir < 0) {
    digitalWrite(LEFT_MOTOR_1, HIGH);
    digitalWrite(LEFT_MOTOR_2, LOW);
  }
  else {
    digitalWrite(LEFT_MOTOR_1, LOW);
    digitalWrite(LEFT_MOTOR_2, HIGH);
  }
}

void setRightMotorDirection(int8_t dir) {
  if(dir < 0) {
    digitalWrite(RIGHT_MOTOR_1, HIGH);
    digitalWrite(RIGHT_MOTOR_2, LOW);
  }
  else {
    digitalWrite(RIGHT_MOTOR_1, LOW);
    digitalWrite(RIGHT_MOTOR_2, HIGH);
  }
}

void brake() {
  turning = 0;
  driving = 0;
  analogWrite(LEFT_POWER, 0);
  digitalWrite(LEFT_MOTOR_1, HIGH);
  digitalWrite(LEFT_MOTOR_2, HIGH);
  analogWrite(RIGHT_POWER, 0);
  digitalWrite(RIGHT_MOTOR_1, HIGH);
  digitalWrite(RIGHT_MOTOR_2, HIGH);
}

/* xPower = -1 to 1
 * ypower = -1 to 1
 * output powers are from -1 to 1
 */
void arcadeDrive(float xPower, float yPower, float* leftOutput, float* rightOutput) {
  //  if x negative, turning left; otherwise, turning right
  if (xPower < 0) {
    *leftOutput = yPower * (1 + (2 * xPower)); // left motor reduced for right turn
    *rightOutput = yPower;                           // right motor not changed
  }
  else {
    *rightOutput = yPower * (1 - (2 * xPower)); // right motor reduced for left turn
    *leftOutput = yPower;                            // left motor not changed
  }
}

void turn(float angle) {
  pid_sat_reset((pid_sat_t*)&turn_pid);
  pid_sat_set_setpoint((pid_sat_t*)&turn_pid, angle);
  turning = 1;
}

uint8_t isTurning() {
  return turning;
}

void drive(float newSpeed, float angle) {
  pid_sat_reset((pid_sat_t*)&drive_pid);
  pid_sat_set_setpoint((pid_sat_t*)&drive_pid, angle);
  driveSpeed = newSpeed;
  driving = 1;
}

uint8_t isDriving() {
  return driving;
}

void updatePID(float yaw) {
  if(turning) {
    updateTurnPID(yaw);
  }
  if(driving) {
    updateDrivePID(yaw);
  }
}

volatile uint8_t distanceUpdateCounter = 0;

void updateDrivePID(float yaw) {
  //make it so that values below 0 don't jump to 360
  if(yaw > 180) {
    yaw -= 360;
  }
  
  float adjustedYaw = constrain(floatMap(yaw, -180, 180, -1, 1), -1, 1);

  if(1) {
    //calculate some adjustment based on distance sensors
    int difference = getRightDistance()-getLeftDistance();
    float newSetpoint = constrain(difference*HORIZONTAL_ADJUSTMENT_COEFFICIENT, -1, 1);
    pid_sat_set_setpoint((pid_sat_t*)&drive_pid, newSetpoint);
    distanceUpdateCounter = 0;
  }

  distanceUpdateCounter++;
  
  // generate our PID controller output
  float output = -pid_sat_update((pid_sat_t*)&drive_pid, adjustedYaw);
  
  //Now, calculate the left and right wheel powers
  float leftPower = 0, rightPower = 0;
  arcadeDrive(output, driveSpeed, &leftPower, &rightPower);

  //Set motor directions based on sign
  //if output is positive, it means we need to turn more clockwise,
  //so left motor forward and right motor backward. Vice versa for
  //counterclockwise
  setLeftMotorDirection((leftPower > 0) ? 1 : -1);
  setRightMotorDirection((rightPower > 0) ? 1 : -1);

  //Set the wheel powers, and scale and constrain them to the right range
  float leftAnalog = constrain(floatMap(fabs(leftPower), 0, 1, 0, 255), 0, 255);
  float rightAnalog = constrain(floatMap(fabs(rightPower), 0, 1, 0, 255), 0, 255);
  analogWrite(LEFT_POWER, leftAnalog);
  analogWrite(RIGHT_POWER, rightAnalog);
  
}

void updateTurnPID(float yaw) {
  // generate our PID controller output
  float output = -pid_sat_update((pid_sat_t*)&turn_pid, yaw);

  //Set motor directions based on sign
  //if output is positive, it means we need to turn more clockwise,
  //so left motor forward and right motor backward. Vice versa for
  //counterclockwise
  int8_t outputSign = (output > 0) ? 1 : -1;
  setLeftMotorDirection(outputSign);
  setRightMotorDirection(-outputSign);
  
  //Set the wheel powers, and scale and constrain them to the right range
  float leftAnalog = constrain(floatMap(fabs(output), 0, 1, 0, 255), 0, 255);
  float rightAnalog = constrain(floatMap(fabs(output), 0, 1, 0, 255), 0, 255);

  //if the same two values are being assigned over and over, then the robot doesnt need to turn anymore
  if(leftAnalog == prevVal) {
    zeroCount++;
  }
  else {
    zeroCount = 0;
    prevVal = leftAnalog;
  }

  if(zeroCount > 5) {
    brake();
    zeroCount = 0;
  }
  else {
    analogWrite(LEFT_POWER, leftAnalog);
    analogWrite(RIGHT_POWER, rightAnalog);
  }
  
}

void TCC0_Handler() {
  if(TCC0->INTFLAG.bit.OVF == 1) 
  {
    TCC0->INTFLAG.bit.OVF = 1; // clear flag
    
    float x = 0, y = 0, z = 0;
    getOrientation(&x, &y, &z);
    updatePID(x);
  }
}



