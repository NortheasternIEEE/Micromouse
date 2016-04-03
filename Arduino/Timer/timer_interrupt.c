/* Timer set up code. The TCC data type is a structure that defines the 
configuration of a timer-> The following code is for an Arduino Zero board. 

The fields of the structure and their respective roles are as follows:

  PER: defines the number at which an interrupt will occur. 
  WAVE: defines the output waveform. 
  CC[x]: determines the timer being operated on. 
  
  Credit: Markus Bader
*/

void setup()
{
  //SET UP FOR CONFIGURATION-------------------------------------------------------------------------------
  
  //Start by initializing the clock that will drive the timer-> 
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
  
  timer->PER.reg = 0xFFFF; //Set TOP value in PER register.  
  while(timer->SYNCBUSY.bit.PER == 1); 
  
  timer->CC[0].reg = 0xFFF; 
  while(timer->SYNCBUSY.bit.CC0 == 1); 
  
  // INTERRUPT SELECTION ------------------------------------------------------------------------------------
  timer->INTENSET.reg = 0;
  timer->INTENSET.bit.OVF = 1; 
  
}

void loop()
{
  //Empty
}

void TCC0_Handler() 
{
  Tcc timer = (Tcc*) TCC0;
  if(timer->INTFLAG.bit.OVF == 1) 
  {
    //Do stuff
    timer->INTFLAG.bit.OVF = 0; // clear flag. 
  }
}