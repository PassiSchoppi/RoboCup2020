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

uint8_t sensorData[15];
uint8_t state;

void setup() {
	// stabilize und dann entscheiden
	state = 8;

	// ## INIT ##
  	motorInit();
	sensorInit();
	melexisInit();
	mapInit();
	timerInit();
	
	Serial.begin(2000000);
}


void loop() {
	// ## LED ##
	digitalWrite(13, !digitalRead(13));

	// ## SENSORS ##
	sensorRead(&sensorData[0]);
	
	// kitdropperSetTo(0);

	// motorDriveTo(FRONT, 100);

	// ## STATE ##
	// stateChange(&state, &sensorData[0]);
	// Serial.println(state);

	// ## OUTPUT ##
    // # MOTOREN #
	/*Serial.print(motorStepsMade(0));Serial.print(" ");
	 Serial.print(motorStepsMade(1));Serial.print(" ");
	 Serial.print(motorStepsMade(2));Serial.print(" ");
	 Serial.println(motorStepsMade(3));*/
	// # SIDE SHARPS #
	// Serial.println(sensorData[0]);Serial.print(" ");
	 // Serial.println(sensorData[1]);Serial.print(" ");
	 // Serial.println(sensorData[2]);Serial.print(" ");
	 // Serial.println(sensorData[3]);Serial.print(" ");
	// # ACC #
	/*Serial.print(sensorData[4]);Serial.print(" ");
	 Serial.println(sensorData[5]);*/
	// # FRONT/BACK SHARPS #
	// Serial.print(sensorData[6]);Serial.print(" ");
	 // Serial.println(sensorData[7]);Serial.print(" ");
	 // Serial.print(sensorData[8]);Serial.print(" ");
	 Serial.println(sensorData[9]);Serial.print(" ");
	 // Serial.println(sensorData[10]);
	// # MELEXIS #
	// melexisChangeAddress(0xA0);
	/*Serial.print(sensorData[11]);Serial.print(" ");
	 Serial.println(sensorData[12]);*/
	// # LIGHT #
	/*Serial.print(sensorData[13]);Serial.print(" ");
	 Serial.println(sensorData[14]);*/
	// # ISWALL #
	/*Serial.print(wallExists(FRONT, &sensorData[0]));Serial.print(" ");
	 Serial.print(wallExists(RIGHT, &sensorData[0]));Serial.print(" ");
	 Serial.print(wallExists(LEFT, &sensorData[0]));Serial.print(" ");
	 Serial.println(wallExists(BACK, &sensorData[0]));*/
}

