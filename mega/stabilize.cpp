#include "stabilize.h"

void stabilize(){
	/*motorBrake();
	int i=0;
	uint8_t localSensorData[15];
	readSensor(&localSensorData[0]);
	while( abs(localSensorData[0]-localSensorData[1]) > 1 ){
		readSensor(&localSensorData[0]);
		if( isWall(LEFT, &localSensorData[0]) ){
			motorSetSpeed(1, 50*(localSensorData[0]-localSensorData[1])/abs(localSensorData[0]-localSensorData[1]));
			motorSetSpeed(0, 50*(localSensorData[0]-localSensorData[1])/abs(localSensorData[0]-localSensorData[1]));
		}else{
			// motorBrake();
			// resetAllSteps();
			return;
		}
		++i;
		if( i>1000 ){
			motorBrake();
			resetAllSteps();
			return;
		}
	}
	motorBrake();
	resetAllSteps();*/
}
