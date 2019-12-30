#include <Arduino.h>
#include "state.h"
#include "motor.h"
#include "pid.h"
#include "sensor.h"
#include "wall.h"
#include "led.h"
#include "config.h"

uint8_t nothing(){
	return 0;
}

void changeState(uint8_t *state, uint8_t *sensorData){
	switch(*state) {
		case 0 :
			*state = nothing();
			setLED(OFF);
			break;
		case 1 :
			// Serial.println("state 1");
			// motorSetLeftSpeed(pid(75, sensorData[0], sensorData[1], true));
			// motorSetRightSpeed(pid(75, sensorData[2], sensorData[3], true));
			if(isWall(RIGHT, &sensorData[0])){
				Serial.println("wall in front");
				*state = 0;
			}
			setLED(WHITE);
			break;
	}
}
