#ifndef SENSORS_H_
#define SENSORS_H_

#include "Arduino.h"

#define BNO055_SAMPLERATE_DELAY_MS (1)

void sensorsInit(void);

//-------- ORIENTATION --------//
void getOrientation(float*, float*, float*);

//-------- ENCODERS --------//

#define LEFT_ENCODER_CLK   12
#define LEFT_ENCODER_MISO  24
#define RIGHT_ENCODER_CLK  23
#define RIGHT_ENCODER_MISO 22

//distance betwen cells is 18 cm
//REMEMBER to change back to 18 day of competition
#define DISTANCE_BETWEEN_CELLS (18.5)

/*The reason we chose 50 is the 50 to 1 gear ratio, and the 3 comes \
 * from the encoder poles when we are just using the rising edge
 */
#define TICKS_IN_ONE_REVOLUTION ((float)50*3)

//(50*3*18/12.566)
//REMEMBER to change to 18 day of competition
#define WHEEL_CIRCUMFERENCE 12.566
//(m/cell)/(m/rev) = rev/cell ---> (rev/cell)*(ticks/rev) = ticks/cell
#define TICKS_PER_CELL (TICKS_IN_ONE_REVOLUTION*DISTANCE_BETWEEN_CELLS/WHEEL_CIRCUMFERENCE)

float getPosition(void);
uint32_t getLeftEncoder(void);
uint32_t getRightEncoder(void);

//-------- DISTANCE --------//

#define PING_POWER            A0
#define FRONT_DISTANCE_SENSOR A4
#define BACK_DISTANCE_SENSOR  A3

#define LEFT_CE 11
#define NEW_RIGHT_ADDRESS 0x09

#define LEFT_DISTANCE_OFFSET 4

uint8_t getLeftDistance(void);
uint8_t getRightDistance(void);
float getFrontDistance(void);
float getBackDistance(void);

#endif

