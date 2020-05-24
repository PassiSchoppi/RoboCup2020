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
	// FIXME: half of MAPSIZE
	robot_is_at.X = 5;
	robot_is_at.Y = 5;
}


void mapUpdateField()
{
	// add walls to current field
	Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( FRONT ) ] = wallExists(FRONT);
	Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( RIGHT ) ] = wallExists(RIGHT);
	Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( BACK ) ] = 	wallExists(BACK);
	Map[robot_is_at.X][robot_is_at.Y].directions[ mapDirectionToCompas( LEFT ) ] = 	wallExists(LEFT);
	
	// change walls of sourounding
	Map[robot_is_at.X][robot_is_at.Y-1].directions[ SOUTH ] = 	Map[robot_is_at.X][robot_is_at.Y].directions[NOTH];
	Map[robot_is_at.X+1][robot_is_at.Y].directions[ WEST ] = 	Map[robot_is_at.X][robot_is_at.Y].directions[EAST];
	Map[robot_is_at.X][robot_is_at.Y+1].directions[ NOTH ] = 	Map[robot_is_at.X][robot_is_at.Y].directions[SOUTH];
	Map[robot_is_at.X-1][robot_is_at.Y].directions[ EAST ] = 	Map[robot_is_at.X][robot_is_at.Y].directions[WEST];

	// mark current field as visited
	Map[robot_is_at.X][robot_is_at.Y].visited = true;
	
}


void mapMoveTo(uint8_t directionToGo)
{
	switch( mapDirectionToCompas( directionToGo ) ) {
		case NOTH:
			robot_is_at.Y -= 1;
			robot_is_facing = NOTH;
			break;
		case EAST:
			robot_is_at.X += 1;
			robot_is_facing = EAST;
			break;
		case SOUTH:
			robot_is_at.Y += 1;
			robot_is_facing = SOUTH;
			break;
		case WEST:
			robot_is_at.X -= 1;
			robot_is_facing = WEST;
			break;
	}
}

void mapBlackFieldFront(uint8_t *robot_is_facing, Vector *robot_is_at)
{
}

uint8_t mapSearchForUnvisited(Vector startPoint, Vector *skip, bool returnBestDirection) 
{
	// check if startpoit is unvisited
	if(Map[ startPoint.X ][ startPoint.Y ].visited == false)
	{
		return(1);
	}

	// add startpoint to end of skip array
	uint8_t i=0;
	while((skip[i].X != 0) && (skip[i].Y != 0))
	{
		++i;
	}
	skip[i] = startPoint;

	/*for(uint8_t i=0; i<100; ++i)
	{
		Serial.print("[");
		Serial.print(skip[i].X);Serial.print(", ");Serial.print(skip[i].Y);Serial.print("]  ");
	}
	Serial.println();
	*/

	// for every direction check if there is an unvisited
	Vector child;
	uint8_t results[4];

	// NOTH child
	child.X = startPoint.X;
	child.Y = startPoint.Y - 1;
	// no wall in NOTH      &&     not in the skip array
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[NOTH] && !mapFieldInSkip( child, skip));
	{
		// distance to nearest unvisited
		results[ NOTH ] = mapSearchForUnvisited( child, skip, false);
	}
	// EAST child
	child.X = startPoint.X + 1;
	child.Y = startPoint.Y;
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[EAST] && !mapFieldInSkip( child, skip ))
	{
		results[ EAST ] = mapSearchForUnvisited( child, skip, false);
	}
	// SOUTH child
	child.X = startPoint.X;
	child.Y = startPoint.Y + 1;
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[SOUTH] && !mapFieldInSkip( child, skip ))
	{
		results[ SOUTH ] = mapSearchForUnvisited( child, skip, false);
	}
	// WEST child
	child.X = startPoint.X - 1;
	child.Y = startPoint.Y;
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[WEST] && !mapFieldInSkip( child, skip ))
	{
		results[ WEST ] = mapSearchForUnvisited( child, skip, false);
	}

	uint8_t resultIndex = indexofSmallestElement( &results[0] );
	if ( returnBestDirection )
	{
		return( resultIndex );
	}

	if ( resultIndex != 5 ){
		return( results[ resultIndex ]+1 );
	}else{
		return(0);
	}

}


bool mapFieldInSkip(Vector field, Vector *skip)
{ 	
	// checks if field is in skip
	for(uint8_t i=0; i<100; ++i)
	{
		if( (skip[i].X == field.X) && (skip[i].Y == field.Y) )
		{
			return(true);
		}
	}
	return(false);
}


uint8_t indexofSmallestElement(uint8_t array[4])
{
	/*Serial.print("distances: ");
	Serial.print(array[0]);Serial.print(" ");
	Serial.print(array[1]);Serial.print(" ");
	Serial.print(array[2]);Serial.print(" ");
	Serial.println(array[3]);*/

	uint8_t index;

	if(array[index]!=0){
		index = 0;
	}else if(array[1]!=0){
		index = 1;
	}else if(array[2]!=0){
		index = 2;
	}else if(array[3]!=0){
		index = 3;
	}else{
		return(5);
	}

    for(int i = 1; i < 4; i++)
    {
        if(array[i] < array[index] && array[i]!=0)
            index = i;              
    }

    return index;
}


uint8_t mapWhereToDrive(Vector *robot_is_at) 
{
}


void mapDisplay()
{
	Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
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
		Vector skip[100];
		Vector test;
		test.X = i;
		test.Y = o;
		// skip[0] = *robot_is_at;
		Serial.print( mapSearchForUnvisited( test, skip, true ) );
		// if ( Map[i][o].visited )
			// Serial.print("V");
		// else
			// Serial.print("X");
		

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
