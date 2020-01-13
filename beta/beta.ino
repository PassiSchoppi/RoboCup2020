#include "Arduino.h"
#include "config.h"

uint8_t bufferVar;

void setup() {
	pinMode(INTERUPT_PIN, INPUT_PULLUP);
	pinMode(SHP_FL, INPUT);
	pinMode(SHP_FC, INPUT);
	pinMode(SHP_FR, INPUT);
	pinMode(SHP_BL, INPUT);
	pinMode(SHP_BR, INPUT);
	pinMode(LED_R, INPUT);
	pinMode(LED_G, INPUT);
	pinMode(LED_B, INPUT);
	Serial.begin(4800);
	attachInterrupt(digitalPinToInterrupt(INTERUPT_PIN), interupt, RISING);
}

void loop() {
	//              EDIT THIS \/ \/ \/

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
	while(Serial.available()){
		bufferVar = Serial.read();
		switch(bufferVar) {
			case 0:
				digitalWrite(LED_R, LOW);
				digitalWrite(LED_G, LOW);
				digitalWrite(LED_B, LOW);
				break;
			case 1:
				digitalWrite(LED_R, HIGH);
				digitalWrite(LED_G, HIGH);
				digitalWrite(LED_B, HIGH);
				break;
			case 2:
				digitalWrite(LED_R, HIGH);
				digitalWrite(LED_G, LOW);
				digitalWrite(LED_B, LOW);
				break;
			case 3:
				digitalWrite(LED_R, LOW);
				digitalWrite(LED_G, HIGH);
				digitalWrite(LED_B, LOW);
				break;
			case 4:
				digitalWrite(LED_R, LOW);
				digitalWrite(LED_G, LOW);
				digitalWrite(LED_B, HIGH);
				break;
			case 5:
				digitalWrite(LED_R, HIGH);
				digitalWrite(LED_G, LOW);
				digitalWrite(LED_B, HIGH);
				break;
			case 6:
				digitalWrite(LED_R, HIGH);
				digitalWrite(LED_G, HIGH);
				digitalWrite(LED_B, LOW);
				break;
			case 7:
				digitalWrite(LED_R, LOW);
				digitalWrite(LED_G, HIGH);
				digitalWrite(LED_B, HIGH);
				break;
		}
	}
}

void interupt(){
	uint8_t sensorData[5];

	sensorData[0] = analogRead(SHP_FL);
	sensorData[1] = analogRead(SHP_FC);
	sensorData[2] = analogRead(SHP_FR);
	sensorData[3] = analogRead(SHP_BL);
	sensorData[4] = analogRead(SHP_BR);

	for(uint8_t i=0; i<5; ++i){
		Serial.write(sensorData[i]);
	}
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(LED_BUILTIN, LOW);
}
