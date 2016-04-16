#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "PID.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define LEFT_POWER    A1
#define LEFT_MOTOR_1  6
#define LEFT_MOTOR_2  9
#define RIGHT_POWER   A2
#define RIGHT_MOTOR_1 5
#define RIGHT_MOTOR_2 10

#define BNO055_SAMPLERATE_DELAY_MS (1)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

#define Y_SPEED 0.7 //80% speed

volatile pid_sat_t pid;

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

void setup() {

  pinMode(LEFT_POWER, OUTPUT);
  pinMode(LEFT_MOTOR_1, OUTPUT);
  pinMode(LEFT_MOTOR_2, OUTPUT);
  pinMode(RIGHT_POWER, OUTPUT);
  pinMode(RIGHT_MOTOR_1, OUTPUT);
  pinMode(RIGHT_MOTOR_2, OUTPUT);

  Serial.begin(115200);
  
  //Initialize our PID controller
  //pid_sat_init((pid_sat_t*)&pid, 0.001, 0.425, 0.01, -1, 1); //set gains and limits
  pid_sat_init((pid_sat_t*)&pid, 0.005, 0.575, 0.1, -0.65, 0.65);
  pid_set_setpoint((pid_sat_t*)&pid, 90); //desired angle is 0

  //Initialize the gyro
  if (!bno.begin()) {
    //Serial.print("No BNO055 detected");
    while(1);  
  }
  
  //Set up timer interrupt for 10ms
  //Start by initializing the clock that will drive the timer. 
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC0_TCC1) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 );  
  
  // Get the timer structure. Now the fields of timer must be defined. 
  Tcc* timer = (Tcc*) TCC0;
  
  // Disable peripheral so that the timer can be configured. 
  timer->CTRLA.reg &= ~TCC_CTRLA_ENABLE;
  while(timer->SYNCBUSY.bit.ENABLE == 1);
  
  //CONFIGURE FIELDS OF THE STRUCTURE------------------------------------------------------------------------
  timer->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV256; //Set the prescaler
  
  timer->WAVE.reg |= TCC_WAVE_WAVEGEN_NFRQ; //Set wave form configuration
  while(timer->SYNCBUSY.bit.WAVE == 1);
  
  timer->PER.reg = 1874; //48MHz/256 = 187500Hz. We want 10ms intervals, so 187500*0.01s = 1875 ticks, -1 for interval between TOP and clearing 
  while(timer->SYNCBUSY.bit.PER == 1); 
  
  // INTERRUPT SELECTION ------------------------------------------------------------------------------------
  timer->INTENSET.reg = 0;
  timer->INTENSET.bit.OVF = 1; 

   // Enable InterruptVector
  NVIC_EnableIRQ(TCC0_IRQn);

  // Enable TC
  timer->CTRLA.reg |= TCC_CTRLA_ENABLE;
  while (timer->SYNCBUSY.bit.ENABLE == 1); // wait for sync
  
}

void loop() {
  //Empty
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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

void TCC0_Handler() {
  Tcc* timer = (Tcc*) TCC0;
  if(timer->INTFLAG.bit.OVF == 1) 
  {
    timer->INTFLAG.bit.OVF = 1; // clear flag.

    //get the yaw, scale and constrain it
    sensors_event_t event;
    bno.getEvent(&event);
    float yaw = event.orientation.x;
    //make it so that values below 0 don't jump to 360
    /*
    if(yaw > 180) {
      yaw -= 360;
    }
    */
    //Serial.println(yaw);
    
    // generate our PID controller output
    float output = -pid_sat_update((pid_sat_t*)&pid, yaw);

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
    analogWrite(LEFT_POWER, leftAnalog);
    analogWrite(RIGHT_POWER, rightAnalog);
  }
}
