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

uint8_t sensorData[15];
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

	Serial.begin(2000000);

	delay(1000);
}


void loop() 
{

	// ## LED ##
	digitalWrite(13, !digitalRead(13));
	
	// ## SENSORS ##
	// Serial.print("reading Sensor Data ... ");
	sensorRead(&sensorData[0]);
	// Serial.println("done!");
	
	// raspiRead();

	// ## STATE ##
	// Serial.println("changing state ... ");
	stateChange(&state, &sensorData[0], &robot_is_facing, &robot_is_at);
	// Serial.print("done changing State: ");
	// Serial.println(state);
	
	// ## OUTPUT ##
    // # MOTOREN #
	/*Serial.print(motorStepsMade(0));Serial.print(" ");
	 Serial.print(motorStepsMade(1));Serial.print(" ");
	 Serial.print(motorStepsMade(2));Serial.print(" ");
	 Serial.println(motorStepsMade(3));*/
	// # SIDE SHARPS #
	/*Serial.print(sensorData[0]);Serial.print(" ");
	 Serial.print(sensorData[1]);Serial.print(" ");
	 Serial.print(sensorData[2]);Serial.print(" ");
	 Serial.println(sensorData[3]);Serial.print(" ");*/
	// # ACC #
	/*Serial.print(sensorData[4]);Serial.print(" ");
	 Serial.println(sensorData[5]);*/
	// # FRONT/BACK SHARPS #
	/*Serial.print(sensorData[6]);Serial.print(" ");
	 Serial.print(sensorData[7]);Serial.print(" ");
	 Serial.print(sensorData[8]);Serial.print(" ");
	 Serial.print(sensorData[9]);Serial.print(" ");
	 Serial.println(sensorData[10]);*/
	// # MELEXIS #
	/*Serial.print(sensorData[11]);Serial.print(" ");
	 Serial.println(sensorData[12]);*/
	// # LIGHT #
	// Serial.print(sensorData[13]);Serial.print(" ");
	 // Serial.println(sensorData[14]);
	// # ISWALL #
	/*Serial.print("Walls: ");
	 Serial.print(wallExists(FRONT, &sensorData[0]));Serial.print(" ");
	 Serial.print(wallExists(RIGHT, &sensorData[0]));Serial.print(" ");
	 Serial.print(wallExists(LEFT, &sensorData[0]));Serial.print(" ");
	 Serial.println(wallExists(BACK, &sensorData[0]));*/
}

