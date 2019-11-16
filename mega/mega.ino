#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"

void setup() {
  	// put your setup code here, to run once:
  	Serial.begin(9600);
	Serial1.begin(9600);
	motorInit();
	sensorInit();
	initMap();
}

void loop() {
	// readSensor();
	motorSetLeftSpeed(75);
	motorSetRightSpeed(75);
}
