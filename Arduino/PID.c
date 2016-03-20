/* PID is a structure that keeps the robot on track. It uses a set 
point (the goal), and p(t) (current location) to determine where
it wants to go. The PID structure will be created to represent the
gyro (to ensure the appropriate orientation), and encoders (to 
ensure the proper distance was travelled). 

A PID is a struct. It has five fields: 
gainP: constant, used to scale error.
gainI: constant, used to scale integrated error.
gainD: constant, used to scale differential error. 
accumulation: used to track the integrated error. 
previousError: used to track the differential error. 

METHODS: 
The following functions will be applied to the PID, but will be 
ordinary functions elsewhere in the code. 
*/
struct PID {
	uint16_t gainP;
	uint16_t gainI;
	uint16_t gainD;
	uint16_t accumulation = 0;
	uint16_t previousError = 0; 
}

//location, setPoint-> error 
//computes the error for a sensor at time. 
uint16_t error(uint16_t location, uint16_t setPoint) { 
	error = location - sensor; 
	return error;
}

//PID, location, setPoint -> PID error 
uint16_t PIDoutput(PID sensor, uint16_t location, uint16_t setPoint) {
	uint16_t e = error(location, setPoint);
	
	setAccumulation(sensor, e);
	
	uint16_t p = sensor.gainP * e;
	
	uint16_t i = sensor.gainI * sensor.accumulation;
	
	uint16_t d = sensor.gainD * (location - sensor.previousError);
	setPreviousError(sensor, location);
	
	return  p + i + d; 
}

// PID sensor, error -> sensor.accumulation 
void setAccumulation(PID sensor, uint16_t error) {
	sensor.accumulator = sensor.accumulator + error;
}

// PID sensor, error -> sensor.previousError
void setPreviousError(PID sensor, uint16_t location) {
	sensor.previousError = location; 
}