/* 
PID H-file. Methods are used across all sensors. 
*/

#ifdef PID
#define PID

struct PID {
	uint16_t gainP;
	uint16_t gainI;
	uint16_t gainD;
	uint16_t accumulation = 0;
	uint16_t previousError = 0; 
};

uint16_t error(uint16_t location, uint16_t setPoint);
uint16_t PIDoutput(PID sensor, uint16_t location, uint16_t setPoint);
void setAccumulation(PID sensor, uint16_t error);
void setPreviousError(PID sensor, uint16_t location);

#endif