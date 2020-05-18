#include <Arduino.h>
#include "output.h"
#include "motor.h"
#include "sensor.h"
#include "config.h"


void output()
{
	Serial.println("########################################");
	// # STATE #
	Serial.print("State: 				");Serial.println(state);
	// # MOTOREN #
	Serial.println("Motor Steps: 	");
	Serial.print(" 	Vorne Links: 	");Serial.println(motorStepsMade(0));
	Serial.print(" 	Hinten Links: 	");Serial.println(motorStepsMade(1));
	Serial.print(" 	Vorne Rechts: 	");Serial.println(motorStepsMade(2));
	Serial.print(" 	Hinten Rechts: 	");Serial.println(motorStepsMade(3));
	// # SIDE SHARPS #
	Serial.println("Sharps: 		");
	Serial.print(" 	Links Vorne: 	");Serial.println(sensorData[0]);
	Serial.print(" 	Links Hinten: 	");Serial.println(sensorData[1]);
	Serial.print(" 	Rechts Vorne: 	");Serial.println(sensorData[2]);
	Serial.print(" 	Rechts Hinten: 	");Serial.println(sensorData[3]);
	Serial.print(" 	Front Left: 	");Serial.println(sensorData[6]);
	Serial.print(" 	Front Center: 	");Serial.println(sensorData[7]);
	Serial.print(" 	Front Right: 	");Serial.println(sensorData[8]);
	Serial.print(" 	Back Left: 	");Serial.println(sensorData[9]);
	Serial.print(" 	Back Right: 	");Serial.println(sensorData[10]);
	// # ACC #
	Serial.println("Accelerometer: 	");
	Serial.print(" 	Y: 		");Serial.println(sensorData[4]);
	Serial.print(" 	Z: 		");Serial.println(sensorData[5]);
	// # MELEXIS #
	Serial.println("Melexis: 		");
	Serial.print(" 	Left: 		");Serial.println(sensorData[11]);
	Serial.print(" 	Right: 		");Serial.println(sensorData[12]);
	// # LIGHT #
	Serial.println("Light: 			");
	Serial.print(" 	Right: 		");Serial.println(sensorData[13]);
	Serial.print(" 	Left: 		");Serial.println(sensorData[14]);
	// # ISWALL #
	Serial.println("Walls: ");
	Serial.print(" 	FRONT: 		");Serial.println(wallExists(FRONT, &sensorData[0]));
	Serial.print(" 	RIGHT: 		");Serial.println(wallExists(RIGHT, &sensorData[0]));
	Serial.print(" 	LEFT: 		");Serial.println(wallExists(LEFT, &sensorData[0]));
	Serial.print(" 	BACK: 		");Serial.println(wallExists(BACK, &sensorData[0]));
}
