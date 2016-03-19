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
//Encoder 0 has OUT A going to pin 19
//Encoder 0 has OUT B going to pin 21

//Encoder 1 has OUT A going to pin 20
//Encoder 1 has OUT B going to pin 12

#include "Arduino.h";
#include <digitalWriteFast.h>

int leftEncoder_PIN_A = 19;
int leftEncoder_PIN_B = 21;
int rightEncoder_PIN_A = 20;
int rightEncoder_PIN_B = 12;

volatile int leftEncoderOutA_State = LOW;
volatile int leftEncoderOutB_State = LOW;
volatile int rightEncoderOutA_State = LOW;
volatile int rightEncoderOutB_State = LOW;

void setup() {
  //since working with the zero micro we can do the folowing
  //attachInterrupt(pin, ISR, mode) ;
  //ISR is simply the function that returns no parameters and is called when mode occurs
  //mode defines when interrupt is triggerd
  //see page 364 of http://www.atmel.com/Images/Atmel-42181-SAM-D21_Datasheet.pdf
  
  attachInterrupt(leftEncoder_PIN_A, isr_leftEncoder_OUTA, CHANGE);
  attachInterrupt(leftEncoder_PIN_B, isr_leftEncoder_OUTB, CHANGE);
  attachInterrupt(rightEncoder_PIN_A, isr_rightEncoder_OUTA, CHANGE);
  attachInterrupt(rightEncoder_PIN_B, isr_rightEncoder_OUTB, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (leftEncoderOutA_State == HIGH)
  {
    //add distance of movement
  }
}

void isr_leftEncoder_OUTA ()
{
  leftEncoderOutA_State = HIGH;
}

void isr_leftEncoder_OUTB ()
{
  
}

void isr_rightEncoder_OUTA ()
{
  
}

void isr_rightEncoder_OUTB ()
{
  
}



//Change notes
//Draft 1: initial draft
