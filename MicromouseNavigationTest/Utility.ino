
#include "Utility.h"

void configureTimer(Tcc* timer, IRQn_Type irqn, uint16_t period) {
  //Start by initializing the clock that will drive the timer. 
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC0_TCC1) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 );
  
  // Disable peripheral so that the timer can be configured. 
  timer->CTRLA.reg &= ~TCC_CTRLA_ENABLE;
  while(timer->SYNCBUSY.bit.ENABLE == 1);
  
  //CONFIGURE FIELDS OF THE STRUCTURE------------------------------------------------------------------------
  timer->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV256; //Set the prescaler
  
  timer->WAVE.reg |= TCC_WAVE_WAVEGEN_NFRQ; //Set wave form configuration
  while(timer->SYNCBUSY.bit.WAVE == 1);
  
  timer->PER.reg = period; //48MHz/256 = 187500Hz. We want 10ms intervals, so 187500*0.01s = 1875 ticks, -1 for interval between TOP and clearing 
  while(timer->SYNCBUSY.bit.PER == 1); 
  
  // INTERRUPT SELECTION ------------------------------------------------------------------------------------
  timer->INTENSET.reg = 0;
  timer->INTENSET.bit.OVF = 1; 

   // Enable InterruptVector
  NVIC_EnableIRQ(irqn);

  // Enable TC
  timer->CTRLA.reg |= TCC_CTRLA_ENABLE;
  while (timer->SYNCBUSY.bit.ENABLE == 1); // wait for sync
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


