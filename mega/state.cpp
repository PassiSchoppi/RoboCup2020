#include <Arduino.h>
#include "state.h"
#include "motor.h"
#include "pid.h"

uint8_t nothing(){
	return 0;
}

void changeState(uint8_t *state, uint8_t *sensorData){
	Serial.println(atoi((const char *)state));
	switch(1) {
		case 0 :
			state = nothing();
			break;
		case 1 :
			Serial.println("hello");
			motorSetLeftSpeed(pid(75, sensorData[0], sensorData[1], true));
			motorSetRightSpeed(pid(75, sensorData[2], sensorData[3], true));
			state = 1;
			break;
	}
}
