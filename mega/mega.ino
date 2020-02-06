#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "pid.h"
#include "state.h"
#include "led.h"
#include "buffer.h"
#include "wall.h"

uint8_t sensorData[11];
uint8_t state;

bool lastTimeEncState;

void setup() {
	state = 1;
  	motorInit();
	sensorInit();
	initMap();
	Serial.begin(9600);
	pinMode(A3, INPUT);
	

  	DDRA |= (1 << PA7);
  	DDRA |= (1 << PA5);
  	DDRG |= (1 << PG5);
  
  	DDRC &= ~(1 << PC4);
  	DDRC &= ~(1 << PC6);
  	
	// PORTA |= (1 << PA5);
  	// PORTG |= (1 << PG5);
}
	bool lastState = false;
int counter = 0;
unsigned long loopCnt = 0;


void loop() {
	// ## LED ##
	digitalWrite(13, !digitalRead(13));
	
	// motorSetRightSpeed(70);
	// motorSetLeftSpeed(70);

	// ## SENSORS ##
	readSensor(&sensorData[0]);

	// ## MOTOR ##
	for(uint8_t i=0; i<4; i++){
		checkForStepsMade(i);
	}

	// ## OUTPUT ##
    // # motoren #
	/* Serial.print(stepsMotorMade(0));Serial.print(" ");
	 Serial.print(stepsMotorMade(1));Serial.print(" ");
	 Serial.print(stepsMotorMade(2));Serial.print(" ");
	 Serial.println(stepsMotorMade(3));*/
	// # SIDE SHARPS #
	// Serial.println(sensorData[0]);Serial.print(" ");
	// Serial.print(sensorData[1]);Serial.print(" ");
	// Serial.print(sensorData[2]);Serial.print(" ");
	// Serial.println(sensorData[3]);
	// # TEMP #
	// Serial.println(sensorData[4]);
	// Serial.println(sensorData[5]);
	// # FRONT/BACK SHARPS #
	// Serial.print(sensorData[6]);Serial.print(" ");
	// Serial.print(sensorData[7]);Serial.print(" ");
	// Serial.print(sensorData[8]);Serial.print(" ");
	// Serial.print(sensorData[9]);Serial.print(" ");
	// Serial.println(sensorData[10]);
	// # ISWALL #
	Serial.print(isWall(0, &sensorData[0]));Serial.print(" ");
	 Serial.print(isWall(1, &sensorData[0]));Serial.print(" ");
	 Serial.print(isWall(2, &sensorData[0]));Serial.print(" ");
	 Serial.println(isWall(3, &sensorData[0]));


	// ## state ##
	changeState(&state, &sensorData[0]);
	// Serial.println(state);
	
	//FIXME
	// delay(100000);
}

