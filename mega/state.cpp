#include <Arduino.h>
#include "state.h"
#include "motor.h"
#include "sensor.h"
#include "wall.h"
#include "led.h"
#include "config.h"
#include "stabilize.h"
#include "map.h"

int average;
uint8_t lastState=0;
uint8_t nextState=0;
bool seenVic = false;

uint8_t nothing()
{
	return 0;
}

void stateChange()
{
	switch(state) 
	{
		case 0:
			// the end
			motorBrake();
			state = nothing();
			LEDSetColor(OFF);
			break;
		
		case 1:
			
			motorBrake();
			// Serial.println("new status");
			LEDSetColor(WHITE);
			
			delay(1000);

			mapUpdateField();

			// if black tile
/*			if( sensorData[13]>MAXWHITE || sensorData[14]>MAXWHITE )
			{
				*state = 10;
				break;
			}
*/			
			if ( !DOMAP )
			{
				// ## get direction to drive to ##
				// 																		RECHTSUMFAHRUNG
				
				if(!wallExists(RIGHT))
				{
					// rechts drehen dann gerade aus
					// Serial.println("Rechts abbiegen!");
					state = 2;
					mapMoveTo(RIGHT);
					break;
				}
				if(!wallExists(FRONT))
				{
					// gerade aus
					// Serial.println("Gerade aus!");
					state = 3;
					mapMoveTo(FRONT);
					break;
				}
				if(!wallExists(LEFT))
				{
					// links drehen dann gerade aus
					// Serial.println("Links abbiegen!");
					state = 4;
					mapMoveTo(LEFT);
					break;
				}
				// wenn rechts und forne und links eine wand ist aber hinten keine
				if(!wallExists(BACK))
				{
					// 2x links drehen dann gerade aus
					// Serial.println("Nach hinten!");
					mapMoveTo(BACK);
					state = 5;
					break;
				}
				
				// wenn überall Wände sind:::
				state = 1;
				LEDSetColor(OFF);
			}
			else
			{
				Vector skip[100];
				uint8_t compasToGoTo = mapWhereToDrive();
				switch ( mapCompasToDirection( compasToGoTo ) ) {
					case FRONT:
						state = 3;
						break;
					case RIGHT:
						state = 2;
						break;
					case BACK:
						state = 5;
						break;
					case LEFT:
						state = 4;
						break;
				}
				mapDisplay();
				mapMoveTo( mapCompasToDirection( compasToGoTo ) );
			}
			break;
		
		case 2:
			// turn right und dann gerade aus
			LEDSetColor(GREEN);
			motorDriveTo(RIGHT, BASESPEED);
			// drive RIGHT until average > STEPFFORRIGHT
			average = 0;
			for(uint8_t i=0; i<4; ++i){
				average = average + abs(motorStepsMade(i));
			}
			average = average/4;
			if( average > STEPFFORRIGHT )
			{
				motorResetAllSteps();
				motorBrake();
				stabilize();
				// gerade aus
				state = 3;
			}
			// wenn da ist ein Victim
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = state;
				state = 6;
			}
			break;
		
		case 3:
			// drive staight
			LEDSetColor(BLUE);
			motorDriveTo(FRONT, BASESPEED);
			// gerade aus bis average > STEPSFORONE
			average = 0;
			for(uint8_t i=0; i<4; ++i)
			{
				average = average + motorStepsMade(i);
			}
			average = average/4;
			if( average>STEPSFORONE )
			{
				motorBrake();
				motorResetAllSteps();
				// stabilize und dann neue entscheidung
				state = 8;
			}
			
			// wenn zu nah an einer Wand
			if( sensorData[7]>124 )
			{
				// kurz zurück und dann neu entscheiden
				motorBrake();
				state = 9;
			}
			// wenn Victim
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = state;
				state = 6;
			}
			// wenn ramp
			// if (  )
			break;
		
		case 4:
			// drive left dann gerade aus
			LEDSetColor(RED);
			motorDriveTo(LEFT, BASESPEED);
			// Left until average > STEPSFORLEFT
			average = 0;
			for(uint8_t i=0; i<4; ++i)
			{
					average = average + abs(motorStepsMade(i));
			}
			average = average/4;
			if(average > STEPSFORLEFT)
			{
				motorResetAllSteps();
				stabilize();
				// gerade aus
				state = 3;
			}
			// wen victim
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = state;
				state = 6;
			}
			break;
		
		case 5:
			// drive left then left and then straight
			LEDSetColor(TURQUOISE);
			motorDriveTo(LEFT, BASESPEED);
			// left bis average = STEPSFORLEFT
			average = 0;
			for(uint8_t i=0; i<4; ++i)
			{
				average = average + abs(motorStepsMade(i));
			}
			average = average/4;
			if(average > STEPSFORLEFT)
			{
				motorResetAllSteps();
				stabilize();
				// dann left und dann gerade aus
				state = 4;
			}
			// wenn victim
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = state;
				state = 6;
			}
			break;
		
		case 6:
			// temp victim
			// try for 5 seconds and blink
			// wenn noch kein victim auf dem Feld ist
			if(!seenVic)
			{
				// zweites mal testen und seite herausfinden
				bool victimIsLeftNotRight = false;
				if ( sensorData[11]>VICTIMTEMP )
				{
					victimIsLeftNotRight = true;
				}
				// sekunde 1
				motorBrake();
				LEDSetColor(RED);
				delay(1000);
				// sekunde 2
				LEDSetColor(OFF);
				delay(1000);
				// senkunde 3
				LEDSetColor(RED);
				delay(1000);
				// sekunde 4
				LEDSetColor(OFF);
				delay(1000);
				// sekunde 5
				LEDSetColor(RED);
				delay(1000);
				
				// abwurf
				kitdropperSetTo(POSMIDD);
				delay(1000);
				seenVic = true;
				if( victimIsLeftNotRight )
				{
					kitdropperSetTo(POSLEFT);
				}
				else
				{
					kitdropperSetTo(POSRIGHT);
				}
				// 2 sekunden warten und dann zurück zu mitte
				delay(2000);
				kitdropperSetTo(POSMIDD);
			}
			
			// zurück zu dem was er gerade gemacht hat
			state = lastState;
			break;
		
		case 7:
			// freier State
			break;
		
		case 8:
			// stabilize und dann neu entscheiden
			LEDSetColor(PINK);
			motorBrake();
			stabilize();
			motorBrake();
			motorResetAllSteps();
			state = 1;
			// Serial.print("state: ");
			// Serial.println(*state);
			seenVic = false;
			break;
		
		case 9:
			//kurz zurück fahren
			motorBrake();
			motorResetAllSteps();
			motorDriveTo(BACK, BASESPEED);
			while(motorStepsMade(0)<15){}
			motorResetAllSteps();
			motorBrake();
			// stabilize und dann neu entscheiden
			state = 8;
			break;

		case 10:
			// black tile und dann drive back one field
			motorBrake();
			motorDriveTo(BACK, BASESPEED);
			while(motorStepsMade(0)<STEPSFORONE){}
			motorBrake();
			motorResetAllSteps();
			// write to map
			sensorRead();
			// wenn links eine wand ist muss er 180 drehung machen
			// wenn nicht dann nur links und gerade aus
			if( wallExists(LEFT) )
			{
				state = 5;
			}
			else
			{
				state = 4;
			}
			break;
	}
}
