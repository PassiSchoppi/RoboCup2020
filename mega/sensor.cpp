#include "sensor.h"

void sensorInit(){
	Serial1.begin(19200);
	pinMode(INTERUPT_PIN_A, OUTPUT);

	Serial3.begin(4800);
	pinMode(INTERUPT_PIN_B, OUTPUT);
}

void readSensor(uint8_t *sensorData){
	uint8_t i=0;
	uint8_t bufferVar;

	// 														ALPHA
	digitalWrite(INTERUPT_PIN_A, HIGH);
	digitalWrite(INTERUPT_PIN_A, LOW);
	
	// delay(100);

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

	// delay(100);
	
	while(Serial3.available())
	{
		bufferVar = Serial3.read();
		// Serial.println("i:");
		// Serial.println(i);
		if(i<11){
			// Serial.println(bufferVar);
			if(bufferVar<32){
				bufferVar=32;
			}
			bufferVar=82600 / (25 * bufferVar -32) - 9;
			if(bufferVar>20){
			 	bufferVar=sensorData[i];
			}
			// Serial.println("//");
			// Serial.println(bufferVar);
			sensorData[i]=bufferVar;
			++i;
		}
	}

	// 															TEMP SENSOR
	// sensorData[]
	
	
	// [LF,
	//  LB,
	//  RF,
	//  RB,
	//  ACC_X,
	//  ACC_Z,
	//  FL,
	//  FC,
	//  FR,
	//  BL,
	//  BR,
	//  TEMP_L,
	//  TEMP_R]
} 
