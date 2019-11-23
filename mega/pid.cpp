#include "pid.h"

float pid(uint8_t motorSpeed, uint8_t distanceF, uint8_t distanceB, bool leftSide){
	uint8_t differential = abs( distanceF - distanceB );
	float factor = pow( 0.5, differential );
	if(distanceB > distanceF){
		if( leftSide ){
			motorSpeed += motorSpeed*(1-factor);
		}else{
			motorSpeed -= motorSpeed*(1-factor);
		}
	}else if( distanceB < distanceF ){
		if( leftSide ){
			motorSpeed -= motorSpeed*(1-factor);
		}else{
			motorSpeed += motorSpeed*(1-factor);
		}
	}
	return motorSpeed;
}
