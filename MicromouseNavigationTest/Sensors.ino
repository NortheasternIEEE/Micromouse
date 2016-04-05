
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "imumaths.h"
#include "VL6180X.h"

#include "Sensors.h"

void sensorsInit() {

  Wire.begin();
  
  orientationInit();
  encodersInit();
  distanceInit();
}


//-------- ORIENTATION --------//

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void orientationInit(void);

void orientationInit() {
  if (!bno.begin()) {
    //Serial.print("No BNO055 detected");
    while(1) {
      digitalWrite(13, HIGH);
    }
  }
}

void getOrientation(float* x, float* y, float* z) {
  sensors_event_t event;
  bno.getEvent(&event);
  *x = event.orientation.x;
  *y = event.orientation.y;
  *z = event.orientation.z;
}


//-------- ENCODERS --------//

volatile uint32_t leftTicks = 0;
volatile uint32_t rightTicks = 0;
volatile float previousPosition = 0;
volatile float encoderVelocity = 0;
volatile float encoderPosition = 0;

void ISR_leftEncoder_OUTA(void);
void ISR_rightEncoder_OUTA(void);

void encodersInit(void);

void encodersInit() {
  //Now, initialize encoders
  //Only use 1X decoding
  pinMode(LEFT_ENCODER_A, INPUT);
  pinMode(RIGHT_ENCODER_A, INPUT);
  attachInterrupt(LEFT_ENCODER_A, ISR_leftEncoder_OUTA, RISING);
  attachInterrupt(RIGHT_ENCODER_A, ISR_rightEncoder_OUTA, RISING);

  configureTimer(TCC1, TCC1_IRQn, 1874);
}

//interrupt service request, called when leftEncoderOUTA_State goes High
void ISR_leftEncoder_OUTA()
{
  leftTicks++;
}

//interrupt service request, called when rightEncoderOUTA_State goes High
void ISR_rightEncoder_OUTA()
{
  rightTicks++;
}

void TCC1_Handler() 
{
  if(TCC1->INTFLAG.bit.OVF == 1) 
  {
    //Timer overflowed, 1875 counts/10ms have passed
    TCC1->INTFLAG.bit.OVF = 1; // clear flag
      //where encoder position is the average of the left and right encoders    
    encoderPosition = ((leftTicks + rightTicks)/2.0);
    float dp = encoderPosition - previousPosition; //change in position
    encoderVelocity = ((float)dp)/0.01; //definition of the derivative, and we know it'll be called every 0.01s
    previousPosition = encoderPosition; //update position so that the next time the interrupt is called, we have it
  }
}

//in cm
float getPosition() {
  return (encoderPosition/TICKS_IN_ONE_REVOLUTION) * WHEEL_CIRCUMFERENCE;
}

//in cm/s
float getVelocity() {
  return (encoderVelocity/TICKS_IN_ONE_REVOLUTION) * WHEEL_CIRCUMFERENCE;
}

void resetEncoders() {
  leftTicks = 0;
  rightTicks = 0;
  encoderPosition = 0;
  encoderVelocity = 0;
  previousPosition = 0;
}

//-------- DISTANCE SENSORS --------//

VL6180X rightSensor;
VL6180X leftSensor;

void distanceInit(void);

void distanceInit() {
  //Left and Right Distance Sensors
  // First, let's change the address of the right sensor
  pinMode(LEFT_CE, OUTPUT);
  digitalWrite(LEFT_CE, LOW); //Toggle the left sensor off
  rightSensor.setAddress(NEW_RIGHT_ADDRESS); // Set it to some new address
  pinMode(LEFT_CE, INPUT); // Turn it back on 
  
  // Now, we can configure both sensors normally
  leftSensor.init();
  rightSensor.init();
  leftSensor.configureDefault();
  rightSensor.configureDefault();
  
  leftSensor.setTimeout(500);
  rightSensor.setTimeout(500);
}


uint8_t getLeftDistance() {
  return leftSensor.readRangeSingle();
}

uint8_t getRightDistance() {
  return rightSensor.readRangeSingle();
}


  

