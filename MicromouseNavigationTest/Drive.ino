#include "Drive.h"

//This variable is used to determine when a turn or drive is complete.
//It measures how many consecutive times our PID output is zero.
//if it's zero fo a while, we know that the move is complete, and we can be done.
volatile uint8_t zeroCount = 0;
volatile float prevVal = 0;
volatile uint8_t driving = 0;
volatile uint8_t turning = 0;
volatile float driveSpeed = 0; //the y speed for driving
volatile float targetAngle = 0; //the last angle that we set the bot to

//Track the number of times we've called the drive PID so that we know
//when to adjust our drive based on side measurements
volatile uint8_t distanceUpdateCounter = 0;

//Accumulate difference between sensor measurements to take the measurements
volatile int differenceAccumulator = 0;

//sometimes we want to ignore our counts if we're not in a straight hallway
//so record the number of valid counts we've taken
volatile uint8_t countsTaken = 0;

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

  configureTimer(TCC0, TCC0_IRQn, (1875 * 5) - 1); //configure to execute every 30ms
}

void setLeftMotorDirection(int8_t dir) {
  if (dir < 0) {
    digitalWrite(LEFT_MOTOR_1, HIGH);
    digitalWrite(LEFT_MOTOR_2, LOW);
  }
  else {
    digitalWrite(LEFT_MOTOR_1, LOW);
    digitalWrite(LEFT_MOTOR_2, HIGH);
  }
}

void setRightMotorDirection(int8_t dir) {
  if (dir < 0) {
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

void hardBrake() {
  turning = 0;
  driving = 0;
  setLeftMotorDirection(FORWARD);
  setRightMotorDirection(FORWARD);
  analogWrite(LEFT_POWER, 255);
  analogWrite(RIGHT_POWER, 255);
  delay(1);
  setLeftMotorDirection(BACKWARD);
  setRightMotorDirection(BACKWARD);
  delay(1);
  analogWrite(LEFT_POWER, 0);
  analogWrite(RIGHT_POWER, 0);
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
  float newTheta = targetAngle + angle;
  if (newTheta < 0) {
    newTheta += 360;
  }
  else if (newTheta >= 360) {
    newTheta -= 360;
  }
  turnAbsolute(newTheta);
}

void turnAbsolute(float angle) {
  targetAngle = angle;
  pid_sat_reset((pid_sat_t*)&turn_pid);
  pid_sat_set_setpoint((pid_sat_t*)&turn_pid, 0);
  turning = 1;
}

uint8_t isTurning() {
  return turning;
}

void drive(float newSpeed) {
  //clear variables from previous driving
  distanceUpdateCounter = 0;
  differenceAccumulator = 0;
  countsTaken = 0;
  pid_sat_reset((pid_sat_t*)&drive_pid);
  pid_sat_set_setpoint((pid_sat_t*)&drive_pid, 0);
  driveSpeed = newSpeed;
  driving = 1;
}

void driveDistance(float distance, float newSpeed) {
  resetEncoders();
  drive(newSpeed);
  //apply the sketchy encoder adjustment formula
  float adjustedDistance = distance;//SKETCHY_ADJUSTMENT_FORMULA(distance);
  float initialPosition = getPosition();
  while (getPosition() < initialPosition + adjustedDistance);
  brake();
  driveCorrect();
}

void driveCorrect() {
  pid_sat_init((pid_sat_t*)&turn_pid, DRIVE_CORRECT_KP, DRIVE_CORRECT_KI, DRIVE_CORRECT_KD, TURN_MIN, TURN_MAX);
  pid_sat_reset((pid_sat_t*)&turn_pid);
  pid_sat_set_setpoint((pid_sat_t*)&turn_pid, 0);
  turning = 1;
  while (isTurning());
  brake();
  pid_sat_init((pid_sat_t*)&turn_pid, TURN_KP, TURN_KI, TURN_KD, TURN_MIN, TURN_MAX);
}

uint8_t isDriving() {
  return driving;
}

void updatePID(float yaw) {
  //make our process variable d[theta]
  //our setpoint is zero, meaning our PID will push the robot towards a d[theta] of zero
  //calculate dtheta using a piecewise function
  float dtheta = 0;
  if (fabs(targetAngle - yaw) > 180) {
    dtheta = (360 - fabs(targetAngle - yaw)) * signum(yaw - targetAngle);
  }
  else {
    dtheta = targetAngle - yaw;
  }
  //Serial.println(dtheta);
  
  if (turning) {
    updateTurnPID(dtheta);
  }
  if (driving) {
    updateDrivePID(dtheta);
  }
}

void updateDrivePID(float dtheta) {
  if (distanceUpdateCounter % 2) {
    uint8_t left = getLeftDistance();
    uint8_t right = getRightDistance();
    if (fabs(left - right) < 120) {

      differenceAccumulator += right - left;
      countsTaken++;
    }
  }

  if (countsTaken >= LR_COUNTS) {
    digitalWrite(13, HIGH);
    //calculate some adjustment based on distance sensors
    float difference = ((float)differenceAccumulator) / ((float)countsTaken);
    differenceAccumulator = 0;
    countsTaken = 0;
    float newSetpoint = -constrain(difference * LATERAL_ADJUSTMENT_COEFFICIENT, LATERAL_ADJUSTMENT_MIN, LATERAL_ADJUSTMENT_MAX);
    pid_sat_set_setpoint((pid_sat_t*)&drive_pid, newSetpoint);
    distanceUpdateCounter = 0;
  }
  else {
    distanceUpdateCounter++;
  }
  // generate our PID controller output
  float output = pid_sat_update((pid_sat_t*)&drive_pid, dtheta);

  Serial.println(output);

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

void updateTurnPID(float dtheta) {
  // generate our PID controller output
  float output = pid_sat_update((pid_sat_t*)&turn_pid, dtheta);

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
  if (leftAnalog == prevVal && leftAnalog < STOP_THRESHOLD) {
    zeroCount++;
  }
  else {
    zeroCount = 0;
    prevVal = leftAnalog;
  }

  if (zeroCount > 5) {
    brake();
    zeroCount = 0;
  }
  else {
    analogWrite(LEFT_POWER, leftAnalog);
    analogWrite(RIGHT_POWER, rightAnalog);
  }

}

void TCC0_Handler() {
  if (TCC0->INTFLAG.bit.OVF == 1)
  {
    TCC0->INTFLAG.bit.OVF = 1; // clear flag

    float x = 0, y = 0, z = 0;
    getOrientation(&x, &y, &z);
    updatePID(x);
  }
}



