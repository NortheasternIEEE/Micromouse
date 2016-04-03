#define A_PIN 12
#define B_PIN 24

#define COUNTS_PER_REVOLUTION ((float)(3*50)) //12CPR encoder on a 50:1 gearbox

void aPinHandler(void);
volatile uint32_t encoderPosition = 0;
volatile float encoderVelocity = 0;

void aPinHandler() {
  encoderPosition++;
}

void setup() {
  pinMode(A_PIN, INPUT);
  attachInterrupt(A_PIN, aPinHandler, RISING);

  Serial.begin(115200);

  //we want to use a timer interrupt to poll our position from our variable
  //this gives us a constant time interval, and since we'd know change in position over 
  //change in time, we can calculate velocity
  
  //Start by initializing the clock that will drive the timer
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC0_TCC1) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 );  
  
  // Disable peripheral so that the timer can be configured. 
  TCC0->CTRLA.reg &= ~TCC_CTRLA_ENABLE;
  while(TCC0->SYNCBUSY.bit.ENABLE == 1);
  
  //CONFIGURE FIELDS OF THE STRUCTURE------------------------------------------------------------------------
  TCC0->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV256; //Set the prescaler
  
  TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NFRQ; //Set wave form configuration
  while(TCC0->SYNCBUSY.bit.WAVE == 1);
  
  TCC0->PER.reg = 1874; //48MHz/256 = 187500Hz. We want 10ms intervals, so 187500*0.01s = 1875 ticks, -1 for interval between TOP and clearing
  while(TCC0->SYNCBUSY.bit.PER == 1); 
  
  // INTERRUPT SELECTION ------------------------------------------------------------------------------------
  TCC0->INTENSET.reg = 0;
  TCC0->INTENSET.bit.OVF = 1; 

   // Enable InterruptVector
  NVIC_EnableIRQ(TCC0_IRQn);

  // Enable TC
  TCC0->CTRLA.reg |= TCC_CTRLA_ENABLE ;
  while (TCC0->SYNCBUSY.bit.ENABLE == 1); // wait for sync
}

volatile uint32_t previousPosition = 0;

void TCC0_Handler() 
{
  if(TCC0->INTFLAG.bit.OVF == 1) 
  {
    //Timer overflowed, 1875 counts/10ms have passed
    TCC0->INTFLAG.bit.OVF = 1; // clear flag. 
    uint32_t dp = encoderPosition - previousPosition; //change in position
    encoderVelocity = ((float)dp)/0.01; //definition of the derivative, since we know it'll be called every 0.01s
    previousPosition = encoderPosition; //update position so that the next time the interrupt is called, we have it
  }
}


void loop() {
  //Print values
  //Divide by counts per revolution, since counts/(counts/rev) = counts * (rev/counts) = rev
  // and (counts/sec)/(counts/rev) = (counts/sec)*(rev/counts) = rev/s
  Serial.print("Position: ");
  Serial.print(encoderPosition/COUNTS_PER_REVOLUTION);
  Serial.print("\t");
  Serial.print("Velocity: ");
  Serial.println(encoderVelocity/COUNTS_PER_REVOLUTION);
  delay(100);
}
