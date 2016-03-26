//NU Micromouse Team
//Draft 1: Charlie


//The quadrature encoders use magnetic disc and hall effect sensors 
//hall effect sensor: varies output due to magnetic field 
      //(simple maxwell's equation derivation[change in magnetic field results in an electric current])
//Our sensors operate 2.7V to 18V
//The black disc on the encoder is composed of six magnetic poles (3 north & 3 south) 
//The hall effect sensor is present on the board
//Outputs A and B are driven high (to Vcc) or low (to 0 potential) depending on magnetic field present
//SIDE WITH BUTTON CALLING LEFT! (side note: remember button pushed down is off)
//side without button I am calling the right
//Left encoder is denoted as 0
//Right encoder is Denoted as 1

#include "Arduino.h";

#define leftEncoder_PIN_A = 12;
#define rightEncoder_PIN_A = 23;

//distance betwen cells is 18 cm

#define distanceBetweenCells = .18;

//diameter of the wheel
#define diameterOfWheel = .45

//circumference of the wheel is pie * diameter
#define circumferenceOfWheel = diameterOfWheel*3.14159

/*The reason we chose 50 is the 50 to 1 gear motor, and teh 3 comes \
 * from the encoder
 */
#define encoderTicksOneRevolution = 50*3;
//encoderTicks = (360/circumferenceOfWheel)*distance to travel;
//encoder ticks are the same thing as counts per revolution

//50*3*18/12.5666
#define ticksInOneCell = 215;
int wheelRotations = 0;

/*We know that the distance traveled in one rotation
is equal to pi*diameter of the wheel, and if they rotate twice we 
get twice that amount.
*/

//forward is equal to 1; reverse is equal to 0
#define forward = 1;
#define reverse = 0;

int directionOfBot = forward;

int distanceMovedLeft = 0;
int distanceMovedRight = 0;

#define avgDist() ((distanceMovedLeft + DistanceMovedRight) / 2)

volatile int leftEncoderOutA_State = LOW;
volatile int rightEncoderOutA_State = LOW;

void setup() {
  //since working with the zero micro we can do the folowing
  //attachInterrupt(pin, ISR, mode) ;
  //ISR is simply the function that returns no parameters and is called when mode occurs
  //mode defines when interrupt is triggerd
  //see page 364 of http://www.atmel.com/Images/Atmel-42181-SAM-D21_Datasheet.pdf

  //just declare the number of wheel rotations
  
  
  attachInterrupt(leftEncoder_PIN_A, isr_leftEncoder_OUTA, CHANGE);
  attachInterrupt(rightEncoder_PIN_A, isr_rightEncoder_OUTA, CHANGE);
  //pin 15 for the capture timer interupt
  EVCTRL.TCEI = 1;

  //Pin 28 on the MCU coresspond to I/O TCC0/WO[3]
  //

  
  //EVCTRL.MCEIx = 1;
  //CTRLC.CAPTENx = 1;
  //we want TCCx EV1 which will take the period and pulse width
  //pin 15
  //
}

void loop() {
  while (avgDist() < ticksInOneCell) {
    
  }
  distanceMovedLeft = 0;
  distanceMovedRight = 0;
  
}

void isr_leftEncoder_OUTA ()
{
  distanceMovedLeft += 1;
}

void isr_rightEncoder_OUTA ()
{
  distanceMovedRight += 1;
}

void driveOneCell()
{
  
}



//Change notes
//Draft 1: initial draft
