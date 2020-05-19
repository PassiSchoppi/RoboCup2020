#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "state.h"
#include "led.h"
#include "wall.h"
#include "i2cmaster.h"
#include "melexis.h"
#include "stabilize.h"
#include "timer.h"
#include "kitdropper.h"
#include "raspi.h"
#include "output.h"

// uint8_t sensorData[15];
// ## GLOBAL VARIABLES (see config.h) ##
volatile uint8_t sensorData[15];
uint8_t state;

uint8_t robot_is_facing;
Vector robot_is_at;

void setup() 
{
	// stabilize und dann entscheiden
	state = 8;
	robot_is_facing = NOTH;
	robot_is_at.X = 5;
	robot_is_at.Y = 5;
	
	// ## INIT ##
  	motorInit();
	sensorInit();
	melexisInit();
	mapInit();
	timerInit();
	kitdropperInit();
	raspiInit();

	Serial.begin(1000000);

	// for(int i=0; i<10; ++i)
	// {
		// sensorRead(&sensorData[0]);
	// }
}


void loop() 
{
	digitalWrite(13, !digitalRead(13));
	
	// raspiRead();
	motorDriveTo(FRONT, 100);
	// ## STATE ##
	// Serial.println("changing state ... ");
	// stateChange(&state, &sensorData[0], &robot_is_facing, &robot_is_at);
	// Serial.print("done changing State: ");
	// output();
	motorResetAllSteps();
}
