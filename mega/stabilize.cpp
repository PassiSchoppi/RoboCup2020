#include "stabilize.h"

void stabilize(){
	motorBrake();
	
	uint8_t localSensorData[15];
	for(int i=0; i<1000; ++i){
	
	sensorRead(&localSensorData[0]);

	if( isWall(LEFT, &localSensorData[0]) ){
		motorSetSpeed(1, 50*(localSensorData[0]-localSensorData[1])/abs(localSensorData[0]-localSensorData[1]));
		motorSetSpeed(0, 50*(localSensorData[0]-localSensorData[1])/abs(localSensorData[0]-localSensorData[1]));
	}

	if( isWall(RIGHT, &localSensorData[0]) ){
		motorSetSpeed(2, 50*(localSensorData[2]-localSensorData[3])/abs(localSensorData[2]-localSensorData[3]));
		motorSetSpeed(3, 50*(localSensorData[3]-localSensorData[3])/abs(localSensorData[2]-localSensorData[3]));
	}

	// if( isWall(FRONT, &localSensorData[0]) ){
	// }
	
	}  //ende der for loop

	// ausrichten an der hinteren Wand
	if(isWall(BACK, &localSensorData[0])){
		motorDriveTo(BACK, BASESPEED);
		while(stepsMotorMade(0)<27){
			checkForStepsMade(0);
		}
		motorBrake();
		resetAllSteps();
		motorDriveTo(FRONT, BASESPEED);
		while(stepsMotorMade(0)<27){
			checkForStepsMade(0);
		}
		motorBrake();
		resetAllSteps();
	}

	motorBrake();
	resetAllSteps();
}
