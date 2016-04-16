#define COUNTS_PER_REVOLUTION ((float)(3*50))

void setup() {

  pinMode(13, OUTPUT);
  //Serial.begin(115200);

  //Encoder A channel on PA19: TCC0/WO3
  //Pin 19 is 2*9 + 1, So we will be writing to PMUXO in PMUX9 in PORT Group 0
  //We want Peripheral F

  //C:\Users\billy_000\AppData\Roaming\Arduino15\packages\adafruit\tools\CMSIS\4.0.0-atmel\Device\ATMEL\samd09\include\instance
  //http://asf.atmel.com/docs/3.13.1/samd21/html/struct_port_group.html

  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |    // Divide the 48MHz system clock by 1 = 48MHz
                    GCLK_GENDIV_ID(0);      // Set division on Generic Clock Generator (GCLK) 0
  while (GCLK->STATUS.bit.SYNCBUSY);        // Wait for synchronization

  //Enable clock on clock 0
  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |         // Enable GCLK 0
                     GCLK_GENCTRL_SRC_DFLL48M |   // Set the clock source to 48MHz
                     GCLK_GENCTRL_ID(0);          // Set clock source on GCLK 5
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  //Enable Clock for TCC0
  REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_CLKEN | 
                      GCLK_CLKCTRL_GEN_GCLK0 | 
                      GCLK_CLKCTRL_ID_TCC0_TCC1;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 ); 

  //Enable Clock for EVSYS Channel 5
  REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_CLKEN | 
                      GCLK_CLKCTRL_GEN_GCLK0 | 
                      GCLK_CLKCTRL_ID_EVSYS_5;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 );

  //Enable Clock for EIC
  REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_CLKEN | 
                      GCLK_CLKCTRL_GEN_GCLK0 | 
                      GCLK_CLKCTRL_ID_EIC;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 );
  
  //First, we'll configure the PIO pin to generate an interrupt
  //Set up pin as input, mux to peripheral, set peripheral A
  PORT->Group[0].PINCFG[19].reg |= PORT_PINCFG_PMUXEN | PORT_PMUX_PMUXO_A;

  //Then, configure the external interrupt controller on our pin
  REG_PM_APBAMASK |= PM_APBAMASK_EIC;
  
  //Enable event generation on external interrupt 3
  EIC->EVCTRL.reg |= EIC_EVCTRL_EXTINTEO3;
  //use config[0] because there are 3 configs: one for 0-7, one for 8-15, and one for 24-31
  EIC->CONFIG[0].reg |= EIC_CONFIG_SENSE3_RISE; //Configure for rising edge
  EIC->INTENSET.reg |= EIC_INTENSET_EXTINT3;
  //Enable the external interrupt controller
  EIC->CTRL.reg |= EIC_CTRL_ENABLE;
  while(EIC->STATUS.bit.SYNCBUSY == 1);

  NVIC->ISER[0] = (uint32_t)(1 << ((uint32_t)EIC_IRQn & 0x0000001f));
  /*
  //Then, we'll configure the TCC to receive capture events
  // Disable peripheral so that the timer can be configured. 
  TCC0->CTRLA.reg &= ~TCC_CTRLA_ENABLE;
  while(TCC0->SYNCBUSY.bit.ENABLE == 1);

  //Configure TCC to receive events on channel 3
  TCC0->CTRLA.reg |= TCC_CTRLA_CPTEN3;
  TCC0->EVCTRL.bit.MCEI3 = 1;
  TCC0->EVCTRL.bit.EVACT1 = 0x6; //Configure for PWP, meaning pulse width stored in CC0
  
  TCC0->INTENSET.reg = 0;
  TCC0->INTENSET.reg |= TCC_INTENSET_MC3; 

   // Enable InterruptVector
  NVIC_EnableIRQ(TCC0_IRQn);
  
  // Enable TC
  REG_PM_APBCMASK |= PM_APBCMASK_TCC0;
  TCC0->CTRLA.reg |= TCC_CTRLA_ENABLE ;
  while (TCC0->SYNCBUSY.bit.ENABLE == 1); // wait for sync

  //Last, configure the event system to pass the external interrupt event to the TCC
  
  //Enable power to the event system and reset the system
  REG_PM_APBCMASK |= (PM_APBCMASK_EVSYS);
  EVSYS->CTRL.bit.SWRST = 1;

  //Configure what generates and receives events
  //Use channel 5, hence the 5's
  //Generate an event fron external interrupt 3, datasheet says that this is event generator 0x0F
  //Have TCC0 MC3 receive it, datasheet says set user to 0x9
  
  EVSYS->CHANNEL.reg |= EVSYS_CHANNEL_PATH_SYNCHRONOUS |  //Receive event on rising edge
                        EVSYS_CHANNEL_EVGEN(0x0F) | //Configure the external interrupt to generate the event
                        EVSYS_CHANNEL_CHANNEL(5); //generate event on channel 0
  
  EVSYS->USER.reg |= EVSYS_USER_USER(0x9) | //Configure the user of the event to be TCC0 MC3
                     EVSYS_USER_CHANNEL(5+1); //Configure it to receive event on channel 5

  EVSYS->CTRL.reg |= EVSYS_INTENSET_EVD5;
  
  EVSYS->CTRL.reg |=  EVSYS_CTRL_GCLKREQ; 
  */  
}

volatile uint32_t encoderPosition = 0;
volatile float encoderVelocity = 0;

void loop() {
  // put your main code here, to run repeatedly:
 // Serial.print("Position: ");
 // Serial.print(encoderPosition/COUNTS_PER_REVOLUTION);
 // Serial.print("\t");
 // Serial.print("Velocity: ");
 // Serial.println(encoderVelocity/COUNTS_PER_REVOLUTION);

  delay(100);
}

void EIC_Handler(){
  digitalWrite(13, HIGH);
}

void TCC0_Handler() {
  digitalWrite(13, HIGH);
  if(TCC0->INTFLAG.bit.MC3 == 1) {
    TCC0->INTFLAG.bit.MC3 = 1;
    uint32_t timeSinceLastTick = TCC0->CC[3].reg >> 6;
    float dp = 1; //We know we've only advanced one tick since last capture
    float dt = timeSinceLastTick/48000000.0; //Convert from clock cycles to seconds based on main processor frequency
    encoderVelocity = dp/dt;
    encoderPosition++;
  } 
}

