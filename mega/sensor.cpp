#include "sensor.h"

uint8_t tryMe = 0;

void sensorInit(){
	Serial1.begin(115200);
	pinMode(INTERUPT_PIN_A, OUTPUT);

	Serial3.begin(9600);
	pinMode(INTERUPT_PIN_B, OUTPUT);

	pinMode(7, OUTPUT);
}

void sensorRead(uint8_t *sensorData){
	uint8_t i=0;
	uint8_t bufferVar=0;
	uint8_t newBufferVar;
	
	digitalWrite(INTERUPT_PIN_B, LOW);

	// 														ALPHA
	//wenn noch Daten da sind kein Interrupt
	if(!Serial1.available()){
		digitalWrite(INTERUPT_PIN_A, HIGH);
		digitalWrite(INTERUPT_PIN_A, LOW);
	}
	// warten auf Antwort
	while((Serial1.available()<6)){}
	// Serial.println("got alpha");
	while(Serial1.available())
	{
		bufferVar = Serial1.read();
		if(i<6){
			// Serial.println(bufferVar);
			sensorData[i]=bufferVar;
			++i;
		}
	}
	
	// 														BETA
	// wenn noch daten da sind kein Interrupt
	if(!Serial3.available()){
		digitalWrite(INTERUPT_PIN_B, HIGH);
		digitalWrite(INTERUPT_PIN_B, LOW);
	}
	// auf Antwort warten
	while((Serial3.available()<5)){}
	/*sensorData[6] = Serial3.read();
	sensorData[7] = Serial3.read();
	sensorData[8] = Serial3.read();
	sensorData[9] = Serial3.read();
	sensorData[10] = Serial3.read();*/
	while(Serial3.available())
	{
		bufferVar = Serial3.read();
		if(i<11){
			sensorData[i]=bufferVar;
			++i;
		}
	}

	// 														SENSOR 9 BL
	// sensorData[9] = analogRead(A11) >> 2;

	// 														MELEXIS
	// melexisInterrupt();
	// Serial.println(melexisGetValue(0));
	sensorData[11]=((int)melexisGetValue(0));
	sensorData[12]=((int)melexisGetValue(1));
	
	// 														LIGHT SENSOR
	// digitalWrite(7, HIGH);
	sensorData[13]=(analogRead(A6)>>2)-5;
	sensorData[14]=analogRead(7)>>2;
	digitalWrite(7, LOW);

	//0   [LF,
	//1   LB,
	//2   RF, ???
	//3   RB,
	//4   ACC_X,
	//5   ACC_Z,
	//6   FL,
	//7   FC,
	//8   FR, ???
	//9   BL,
	//10  BR,
	//11  TEMP_L,
	//12  TEMP_R
	//13  LIGHT_R
	//14  LIGHT_L]
}

// dont call this function 255 times
bool dontTryMe() {
	if(tryMe>250){
		tryMe=0;
		Serial.println("fuck");
		return(0);
	}
	++tryMe;
	return(1);
}
