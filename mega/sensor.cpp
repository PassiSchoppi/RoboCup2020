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
	
	delay(10);

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

	delay(10);
	
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
	
	
	//0   [LF,
	//1   LB,
	//2   RF,
	//3   RB,
	//4   ACC_X,
	//5   ACC_Z,
	//6   FL,
	//7   FC,
	//8   FR,
	//9   BL,
	//10  BR,
	//11  TEMP_L,
	//12  TEMP_R]
} 
