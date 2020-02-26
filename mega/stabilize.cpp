#include "stabilize.h"

void stabilize(){
	motorBrake();
	
	uint8_t localSensorData[15];
	for(int i=0; i<1000; ++i){
	
	sensorRead(&localSensorData[0]);

	if( wallExists(LEFT, &localSensorData[0]) ){
		motorSetSpeed(1, 50*(localSensorData[0]-localSensorData[1])/abs(localSensorData[0]-localSensorData[1]));
		motorSetSpeed(0, 50*(localSensorData[0]-localSensorData[1])/abs(localSensorData[0]-localSensorData[1]));
	}

	if( wallExists(RIGHT, &localSensorData[0]) ){
		motorSetSpeed(2, 50*(localSensorData[2]-localSensorData[3])/abs(localSensorData[2]-localSensorData[3]));
		motorSetSpeed(3, 50*(localSensorData[3]-localSensorData[3])/abs(localSensorData[2]-localSensorData[3]));
	}
	
	}  //ende der for loop

	// ausrichten an der hinteren Wand
	if(wallExists(BACK, &localSensorData[0])){
		motorDriveTo(BACK, BASESPEED);
		while(motorStepsMade(0)<27){
			motorCheckForStepsMade(0);
		}
		motorBrake();
		motorResetAllSteps();
		motorDriveTo(FRONT, BASESPEED);
		while(motorStepsMade(0)<27){
			motorCheckForStepsMade(0);
		}
		motorBrake();
		motorResetAllSteps();
	}

	motorBrake();
	motorResetAllSteps();
}
