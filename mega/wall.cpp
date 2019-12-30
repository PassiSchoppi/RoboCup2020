#include "wall.h"
#include "config.h"

bool isWall(uint8_t where, uint8_t *sensorData){
	switch(where) {
		case FRONT :
			// Serial.println(sensorData[6]);
			// Serial.println(sensorData[7]);
			// Serial.println(sensorData[8]);
			if(sensorData[6]<DISTANCETOWALL && sensorData[7]<DISTANCETOWALL && sensorData[8]<DISTANCETOWALL){
				return true;
			}
			break;
		case RIGHT :
			// Serial.println(sensorData[2]);
			// Serial.println(sensorData[3]);
			if(sensorData[2]<DISTANCETOWALL && sensorData[3]<DISTANCETOWALL){
				return true;
			}
			break;
		case BACK :
			// Serial.println(sensorData[9]);
			// Serial.println(sensorData[10]);
			if(sensorData[9]<DISTANCETOWALL && sensorData[10]<DISTANCETOWALL){
				return true;
			}
			break;
		case LEFT :
			// Serial.println(sensorData[0]);
			// Serial.println(sensorData[1]);
			if(sensorData[0]<DISTANCETOWALL && sensorData[1]<DISTANCETOWALL){
				return true;
			}
			break;
	}
	return false;
}
