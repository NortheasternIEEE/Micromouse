#include "MicromousePIDTest.h"
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

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
