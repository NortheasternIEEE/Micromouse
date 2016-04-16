
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

void moveRobot(location *p, direction d) {
    switch (d) {
        case RIGHT:
            // MOVE THE MOUSE RIGHT
            // UPDATE ITS POSITION
            p->x = p->x + 1;
            break;
        case LEFT:
            // MOVE THE MOUSE LEFT
            // UPDATE ITS POSITION
            p->x = p->x - 1;
            break;
        case DOWN:
            // MOVE THE MOUSE DOWN
            // UPDATE ITS POSITION
            p->y = p->y - 1;
            break;
        case UP:
            // MOVE THE MOUSE UP
            // UPDATE ITS POSITION
            p->y = p->y + 1;
            break;
        case STOP:
            // DO NOTHING
            break;
        default:
            break;
    }
}

void initializeLoc(location *spot) {
    spot->x = 0;
    spot->y = 0;
}

void  setLoc(location *spot, int x, int y) {
    spot->x = x;
    spot->y = y;
}

void initializeGraph(node param[mazeSize][mazeSize]) {
    for (int i = 0; i < mazeSize; i ++) {
        for (int j = 0; j < mazeSize; j++) {
            if (i == 0) {
                // IF i == 0 then you are on the left edge of the maze so the mouse can not move left
                param[i][j].left = false;
            } else {
                param[i][j].left = true;
            }
            if (i == mazeSize - 1){
                // if i == mazeSize - 1 you are on the right edge so the mouse can not move right
                param[i][j].right = false;
            } else {
                param[i][j].right = true;
            }
            if (j == 0) {
                // If j == 0 then you are on the bottom edge so the mouse can not move down
                param[i][j].down = false;
            } else {
                param[i][j].down = true;
            }
            if (j == mazeSize -1) {
                // if j == mazeSize - 1 then you are on the top edge so the mouse can not move up
                param[i][j].up = false;
            } else {
                param[i][j].up = true;
            }
            param[i][j].mapped = false;
            param[i][j].parent = STOP;
            param[i][j].x = i;
            param[i][j].y = j;
        }
    }
}

direction goRight(node v) {
    if (v.right) {
        return RIGHT;
    } else {
        return STOP;
    }
}
direction goLeft(node v) {
    if (v.left) {
        return LEFT;
    } else {
        return STOP;
    }
}
direction goUp(node v) {
    if (v.up) {
        return UP;
    } else {
        return STOP;
    }
}
direction goDown(node v) {
    if (v.down) {
        return DOWN;
    } else {
        return STOP;
    }
}

direction reverse(direction d) {
    switch (d) {
        case RIGHT:
            return LEFT;
            break;
        case LEFT:
            return RIGHT;
            break;
        case DOWN:
            return UP;
            break;
        case UP:
            return DOWN;
            break;
        case STOP:
            return STOP;
            break;
        default:
            return STOP;
            break;
    }
}

void clearMapped(node param[mazeSize][mazeSize]) {
    for (int i = 0; i < mazeSize; i ++) {
        for (int j = 0; j < mazeSize; j++) {
            param[i][j].mapped = false;
        }
    }
}




