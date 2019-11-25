#include "sensor.h"

void sensorInit(){
	Serial1.begin(19200);
	pinMode(INTERUPT_PIN_A, OUTPUT);

	Serial2.begin(38400);
	pinMode(INTERUPT_PIN_B, OUTPUT);
}

void readSensor(uint8_t *sensorData){
	uint8_t i=0;
	uint8_t bufferVar;

	// 														ALPHA
	digitalWrite(INTERUPT_PIN_A, HIGH);
	digitalWrite(INTERUPT_PIN_A, LOW);
	
	delay(100);

	while(Serial1.available())
 	{
		bufferVar = Serial1.read();
		if(i<6){
			if(i<4){
				if(bufferVar<32){
					bufferVar=32;
				}
				bufferVar=82600 / (25 * bufferVar - 31) - 9;
				if(bufferVar>20){
					bufferVar=sensorData[i];
				}
			}
			if(i>3 && i<6){}
			sensorData[i]=bufferVar;
			++i;
		}
	}

	// 														BETHA
	digitalWrite(INTERUPT_PIN_B, HIGH);
	digitalWrite(INTERUPT_PIN_B, LOW);

	delay(100);
	
	Serial.write("hey");
	Serial.write(Serial2.available());
	Serial.write(",, ");
	while(Serial2.available())
	{
		bufferVar=2;
		// bufferVar = Serial2.read();
		if(i<10){
			if(bufferVar<32){
				bufferVar=32;
			}
			bufferVar=82600 / (25 * bufferVar -32) - 9;
			if(bufferVar>20){
				bufferVar=sensorData[i];
			}
			sensorData[i]=bufferVar;
			++i;
		}
	}
} 
