/* TCC0 set up code. The TCC data type is a structure that defines the 
configuration of a TCC0. The following code is for an Arduino Zero board. 
The fields of the structure and their respective roles are as follows:
  PER: defines the number at which an interrupt will occur. 
  WAVE: defines the output waveform. 
  CC[x]: determines the TCC0 being operated on. 
  
  
*/

void setup()
{

  pinMode(13, OUTPUT);
  
  //Start by initializing the clock that will drive the TCC0. 
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC0_TCC1) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 );  
  
  // Disable peripheral so that the TCC0 can be configured. 
  TCC0->CTRLA.reg &= ~TCC_CTRLA_ENABLE;
  while(TCC0->SYNCBUSY.bit.ENABLE == 1);
  
  //CONFIGURE FIELDS OF THE STRUCTURE------------------------------------------------------------------------
  TCC0->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV256; //Set the prescaler
  
  TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NFRQ; //Set wave form configuration
  while(TCC0->SYNCBUSY.bit.WAVE == 1);
  
  TCC0->PER.reg = 0xFFFF; //Set TOP value in PER register. 
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

void loop()
{
  //Empty
}

volatile uint8_t ledState = HIGH;

void TCC0_Handler() 
{
  if(TCC0->INTFLAG.bit.OVF == 1) 
  {
    //Do stuff
    TCC0->INTFLAG.bit.OVF = 1; // clear flag. 
    digitalWrite(13, ledState);
    ledState = !ledState;
  }
}
