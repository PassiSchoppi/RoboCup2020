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

uint8_t nothing()
{
	return 0;
}

void stateChange(uint8_t *state, uint8_t *sensorData, uint8_t *robot_is_facing, Vector *robot_is_at)
{
	switch(*state) 
	{
		case 0:
			// the end
			motorBrake();
			*state = nothing();
			LEDSetColor(OFF);
			break;
		
		case 1:
			motorBrake();
			// Serial.println("new status");
			LEDSetColor(WHITE);

			// ## get direction to drive to ##
			// 																		RECHTSUMFAHRUNG
			/*if(!wallExists(RIGHT, &sensorData[0]))
			{
				// rechts drehen dann gerade aus
				Serial.println("Rechts abbiegen!");
				*state = 2;
				break;
			}
			if(!wallExists(FRONT, &sensorData[0]))
			{
				// gerade aus
				Serial.println("Gerade aus!");
				*state = 3;
				break;
			}
			if(!wallExists(LEFT, &sensorData[0]))
			{
				// links drehen dann gerade aus
				Serial.println("Links abbiegen!");
				*state = 4;
				break;
			}
			// wenn rechts und forne und links eine wand ist aber hinten keine
			if(!wallExists(BACK, &sensorData[0]))
			{
				// 2x links drehen dann gerade aus
				Serial.println("Nach hinten!");
				*state = 5;
				break;
			}
			
			// wenn überall Wände sind:::
			*state = 1;
			LEDSetColor(OFF);*/
			

			// 																		MAP
			Serial.print("Facing: ");
			Serial.println(*robot_is_facing);
			mapUpdateField(&*robot_is_facing, &*robot_is_at);
			uint8_t directionToGO;
			directionToGO = mapWhereToDrive(&*robot_is_at);
			Serial.print("direction: ");
			Serial.println(directionToGO);
			switch( directionToGO )
			{
				case NOTH:
					(*robot_is_at).X = (*robot_is_at).X;
					(*robot_is_at).Y -= 1;
					switch( *robot_is_facing )
					{
						case NOTH:
							*robot_is_facing = NOTH;
							*state = 3;
							break;

						case EAST:
							*robot_is_facing = NOTH;
							*state = 4;
							break;

						case SOUTH:
							*robot_is_facing = NOTH;
							*state = 5;
							break;

						case WEST:
							*robot_is_facing = NOTH;
							*state = 2;
							break;
					}
					break;

				case EAST:
					(*robot_is_at).X += 1;
					(*robot_is_at).Y = (*robot_is_at).Y;
					switch( *robot_is_facing )
					{
						case NOTH:
							*robot_is_facing = EAST;
							*state = 2;
							break;

						case EAST:
							*robot_is_facing = EAST;
							*state = 3;
							break;

						case SOUTH:
							*robot_is_facing = EAST;
							*state = 4;
							break;

						case WEST:
							*robot_is_facing = EAST;
							*state = 5;
							break;
					}
					break;

				case SOUTH:
					(*robot_is_at).X = (*robot_is_at).X;
					(*robot_is_at).Y += 1;
					switch( *robot_is_facing )
					{
						case NOTH:
							*robot_is_facing = SOUTH;
							*state = 5;
							break;

						case EAST:
							*robot_is_facing = SOUTH;
							*state = 2;
							break;

						case SOUTH:
							*robot_is_facing = SOUTH;
							*state = 3;
							break;

						case WEST:
							*robot_is_facing = SOUTH;
							*state = 4;
							break;
					}
					break;
				
				case WEST:
					(*robot_is_at).X -= 1;
					(*robot_is_at).Y = (*robot_is_at).Y;
					switch( *robot_is_facing )
					{
						case NOTH:
							*robot_is_facing = WEST;
							*state = 4;
							break;
						
						case EAST:
							*robot_is_facing = WEST;
							*state = 5;
							break;
						
						case SOUTH:
							*robot_is_facing = WEST;
							*state = 2;
							break;

						case WEST:
							*robot_is_facing = WEST;
							*state = 3;
							break;
					}
					break;

				case 5:
					*state = 0;
					break;
			}



			break;
		
		case 2:
			// turn right
			LEDSetColor(GREEN);
			// motorSetRightSpeed(-BASESPEED);
			// motorSetLeftSpeed(BASESPEED);
			motorDriveTo(RIGHT, BASESPEED);
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
				*state = 3;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = *state;
				*state = 6;
			}
			break;
		
		case 3:
			// drive staight
			LEDSetColor(BLUE);
			// motorSetRightSpeed(pid(70, sensorData[2], sensorData[3], false));
			// motorSetLeftSpeed(pid(70, sensorData[0], sensorData[1], true));
			// motorSetRightSpeed(BASESPEED);
			// motorSetLeftSpeed(BASESPEED);
			motorDriveTo(FRONT, BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i)
			{
				average = average + motorStepsMade(i);
			}
			average = average/4;
			if( average>STEPSFORONE )
			{
				motorResetAllSteps();
				// stabilize und dann neue entscheidung
				*state = 8;
			}
			// wenn zu nah an einer Wand
			if( sensorData[7]>132 )
			{
				// kurz zurück und dann neu entscheiden
				motorBrake();
				*state = 9;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = *state;
				*state = 6;
			}
			break;
		
		case 4:
			// drive left
			LEDSetColor(RED);
			// motorSetRightSpeed(BASESPEED);
			// motorSetLeftSpeed(-BASESPEED);
			motorDriveTo(LEFT, BASESPEED);
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
				*state = 3;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = *state;
				*state = 6;
			}
			break;
		
		case 5:
			// drive left
			LEDSetColor(TURQUOISE);
			// motorSetRightSpeed(BASESPEED);
			// motorSetLeftSpeed(-BASESPEED);
			motorDriveTo(LEFT, BASESPEED);
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
				*state = 4;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				lastState = *state;
				*state = 6;
			}
			// if( sensorData[] )
			break;
		
		case 6:
			// temp victim
			motorBrake();
			// try for 5 seconds and blink
			LEDSetColor(RED);
			delay(1000);
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
			{
				LEDSetColor(OFF);
				delay(1000);
				sensorRead(&sensorData[0]);
				if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
				{
					LEDSetColor(RED);
					delay(1000);
					sensorRead(&sensorData[0]);
					if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
					{
						LEDSetColor(OFF);
						delay(1000);
						sensorRead(&sensorData[0]);
						if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
						{
							LEDSetColor(RED);
							delay(1000);
							sensorRead(&sensorData[0]);
							if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP )
							{
								//move the servo motor
								kitdropperSetTo(POSMIDD);
								delay(1000);
								if( sensorData[11]>VICTIMTEMP )
								{
									kitdropperSetTo(POSLEFT);
								}
								else
								{
									kitdropperSetTo(POSRIGHT);
								}
								delay(1000);
								kitdropperSetTo(POSMIDD);
							}
						}
					}
				}
			}
			*state = lastState;
			break;
		
		case 7:
			// black tile
			motorBrake();
			*state = 0;
			break;
		
		case 8:
			// stabilize und dann neu entscheiden
			LEDSetColor(PINK);
			motorBrake();
			stabilize();
			motorBrake();
			motorResetAllSteps();
			*state = 1;
			Serial.print("state: ");
			Serial.println(*state);
			break;
		
		case 9:
			//kurz zurück fahren
			motorBrake();
			motorResetAllSteps();
			motorDriveTo(BACK, BASESPEED);
			while(motorStepsMade(0)<15)
			{
				// motorCheckForStepsMade(0);
			}
			motorResetAllSteps();
			motorBrake();
			// stabilize und dann neu entscheiden
			*state = 8;
			break;
	}
}
