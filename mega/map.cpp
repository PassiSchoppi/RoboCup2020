#include "map.h"


Field Map[MAPSIZE][MAPSIZE];
uint8_t robot_is_facing;
Vector robot_is_at;


// translates direction to compas
uint8_t mapDirectionToCompas(uint8_t directionI)
{
	switch(robot_is_facing)
	{
		// robot is facing NOTH
		case NOTH:
			return(directionI);
			break;
		
		// robot is facing EAST 
		case EAST:
			switch(directionI){
				case FRONT:
					return(EAST);
					break;
				case RIGHT:
					return(SOUTH);
					break;
				case BACK:
					return(WEST);
					break;
				case LEFT:
					return(NOTH);
					break;
			}
			break;
		
		// robot is facing SOUTH
		case SOUTH:
			switch(directionI){
				case FRONT:
					return(SOUTH);
					break;
				case RIGHT:
					return(WEST);
					break;
				case BACK:
					return(NOTH);
					break;
				case LEFT:
					return(EAST);
					break;
			}
			break;
				
		// robot is facing WEST
		case WEST:
			switch(directionI){
				case FRONT:
					return(WEST);
					break;
				case RIGHT:
					return(NOTH);
					break;
				case BACK:
					return(EAST);
					break;
				case LEFT:
					return(SOUTH);
					break;
			}
			break;
	}
}

void mapInit() 
{
	robot_is_facing = NOTH;
	robot_is_at.X = 5;
	robot_is_at.Y = 5;
}


void mapUpdateField()
{
		Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( FRONT ) ]=wallExists(FRONT);
		Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( RIGHT ) ]=wallExists(RIGHT);
		Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( BACK ) ]=wallExists(BACK);
		Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( LEFT ) ]=wallExists(LEFT);
}


void mapBlackFieldFront(uint8_t *robot_is_facing, Vector *robot_is_at)
{
}

uint8_t mapSearchForUnvisited(Vector startPoint, Vector *skip) 
{
}


bool mapFieldInSkip(Vector field, Vector *skip)
{
}


uint8_t indexofSmallestElement(uint8_t array[4])
{
}


uint8_t mapWhereToDrive(Vector *robot_is_at) 
{
}


void mapDisplay()
{
	Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	for (uint8_t o=0; o<MAPSIZE; ++o)
	{
	
	// waende im NORDEN
	for( uint8_t i=0; i<MAPSIZE; ++i )
	{
		if ( Map[i][o].directions[NOTH] )
			Serial.print("@@@");
		else
			Serial.print("   ");
	}
	Serial.println();
	// waende im WESTEN und OSTEN
	for( uint8_t i=0; i<MAPSIZE; ++i )
	{
		// WESTEN
		if ( Map[i][o].directions[WEST] )
		{	
			Serial.print("@");
		}else{
			Serial.print(" ");
		}

		// STATUS
		Serial.print(" ");
		
		// OSTEN
		if ( Map[i][o].directions[EAST] )
		{	
			Serial.print("@");
		}else{
			Serial.print(" ");
		}
	}
	Serial.println();
	// waende im SUEDEN
	for( uint8_t i=0; i<MAPSIZE; ++i )
	{
		if ( Map[i][o].directions[SOUTH] )
			Serial.print("@@@");
		else
			Serial.print("   ");
	}
	Serial.println();
	delay(1);
	}
}
