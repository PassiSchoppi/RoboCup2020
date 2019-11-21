#include "Arduino.h"
#include "config.h"

void setup() {
	pinMode(INTERUPT_PIN, INPUT);
	Serial.begin(19200);
}

void loop() {
	float sensorData[6];

/*
 *
 *           Sensordata in ARRAYINDEX
 *
 *             +-------------------+
 *             |                   |
 *      SHP_LF |  0   ACC_X 4   2  | SHP_RF
 *             |        /|\        |
 *             |         |         |
 *             |         |         |
 *             |         *         |
 *      SHP_LB |  1   ACC_Z 5   3  | SHP_RB
 *             |                   |
 *             +-------------------+ 
 *
 * 
 */

	sensorData[0] = analogRead(SHP_LF);
	sensorData[1] = analogRead(SHP_LB);
	sensorData[2] = analogRead(SHP_RF);
	sensorData[3] = analogRead(SHP_RB);
	sensorData[4] = analogRead(ACC_X);
	sensorData[5] = analogRead(ACC_Z);

	if(digitalRead(INTERUPT_PIN)){
		for(int i=0; i<sizeof(sensorData); ++i){
			Serial.write(round(sensorData[i]));
		}
		delay(100);
	}
}
