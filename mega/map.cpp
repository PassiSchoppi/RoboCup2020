#include "map.h"

Field Map[10][10];
// Vector robot_is_at;

void mapInit() 
{
	// robot_is_at.X = 5;
	// robot_is_at.Y = 5;
}

void mapUpdateField(uint8_t *robot_is_facing, Vector *robot_is_at) 
{
	uint8_t localSensorData[15];
	uint8_t directionsInOrder[4];
	sensorRead(&localSensorData[0]);
	
	// set current field to visited
	Map[(*robot_is_at).X][(*robot_is_at).Y].visited = true;
	
	// link direction and pole
	switch(*robot_is_facing)
	{
		// robot is facing NOTH
		case NOTH:
			// so the direction \/ has \/
			directionsInOrder[FRONT] = NOTH;
			directionsInOrder[RIGHT] = EAST;
			directionsInOrder[BACK] = SOUTH;
			directionsInOrder[LEFT] = WEST;
			break;
		
		// robot is facing EAST 
		case EAST:
			// so the direction \/ has \/
			directionsInOrder[FRONT] = EAST;
			directionsInOrder[RIGHT] = SOUTH;
			directionsInOrder[BACK] = WEST;
			directionsInOrder[LEFT] = NOTH;
			break;
		
		// robot is facing SOUTH
		case SOUTH:
			// so the direction \/ has \/
			directionsInOrder[FRONT] = SOUTH;
			directionsInOrder[RIGHT] = WEST;
			directionsInOrder[BACK] = NOTH;
			directionsInOrder[LEFT] = EAST;
			break;
				
		// robot is facing WEST
		case WEST:
			// so the direction \/ has \/
			directionsInOrder[FRONT] = WEST;
			directionsInOrder[RIGHT] = NOTH;
			directionsInOrder[BACK] = EAST;
			directionsInOrder[LEFT] = SOUTH;
			break;
	}
	
	// write walls to current field
	// i: FRONT, LEFT, RIGHT, BACK
	for(uint8_t i = 0; i < 4; ++i)
	{
		// Map      X                Y          wall in  (NOTH, EAST, SOUTH, WEST) = wall in (FRONT, ...)
		Map[(*robot_is_at).X][(*robot_is_at).Y].directions[directionsInOrder[i]] = wallExists( i, &localSensorData[0]);
	}

	// write fields to surrounding fields
	// NOTH's field SOUTH wall is current's field NOTH wall
	// Map      X                    Y-1         south wall       = Map       X                 Y            north wall
	Map[(*robot_is_at).X][(*robot_is_at).Y - 1].directions[SOUTH] = Map[(*robot_is_at).X][(*robot_is_at).Y].directions[NOTH];

	// EAST field's west wall is current's field EAST wall
	// Map      X+1                  Y           west wall       = Map         X                Y           east wall
	Map[(*robot_is_at).X + 1][(*robot_is_at).Y].directions[WEST] = Map[(*robot_is_at).X][(*robot_is_at).Y].directions[EAST];
	
	// SOUTH's field NOTH wall is current's field SOUTH wall
	// Map      X                    Y+1         noth wall       = Map         X                Y           south wall
	Map[(*robot_is_at).X][(*robot_is_at).Y + 1].directions[NOTH] = Map[(*robot_is_at).X][(*robot_is_at).Y].directions[SOUTH];
	
	// WEST's field EAST wall is current's field WEST wall
	// Map      X-1                  Y           east wall       = Map         X                Y           west wall
	Map[(*robot_is_at).X - 1][(*robot_is_at).Y].directions[EAST] = Map[(*robot_is_at).X][(*robot_is_at).Y].directions[WEST];

	/*Serial.print(Map[robot_is_at.X][robot_is_at.Y].directions[NOTH]);
	Serial.print(Map[robot_is_at.X][robot_is_at.Y].directions[EAST]);
	Serial.print(Map[robot_is_at.X][robot_is_at.Y].directions[SOUTH]);
	Serial.println(Map[robot_is_at.X][robot_is_at.Y].directions[WEST]);*/
}



void mapBlackFieldFront(uint8_t *robot_is_facing, Vector *robot_is_at)
{
	Vector blackField;
	// link direction and pole
	switch(*robot_is_facing)
	{
		case NOTH:
			blackField.X = (*robot_is_at).X;
			blackField.Y = (*robot_is_at).Y - 1;
			break;

		case EAST:
			blackField.X = (*robot_is_at).X + 1;
			blackField.Y = (*robot_is_at).Y;
			break;
				
		case SOUTH:
			blackField.X = (*robot_is_at).X;
			blackField.Y = (*robot_is_at).Y + 1;
			break;
				
		case WEST:
			blackField.X = (*robot_is_at).X - 1;
			blackField.Y = (*robot_is_at).Y;
			break;
	}

	Map[ blackField.X ][ blackField.Y ].directions[ NOTH ] = true;
	Map[ blackField.X ][ blackField.Y ].directions[ EAST ] = true;
	Map[ blackField.X ][ blackField.Y ].directions[ SOUTH ] = true;
	Map[ blackField.X ][ blackField.Y ].directions[ WEST ] = true;


	// write  to surrounding fields
	// NOTH's field SOUTH wall is current's field NOTH wall
	Map[ blackField.X ][ blackField.Y - 1].directions[SOUTH] = Map[ blackField.X ][ blackField.Y ].directions[ NOTH ];

	// EAST field's west wall is current's field EAST wall
	Map[ blackField.X + 1 ][ blackField.Y ].directions[WEST] = Map[ blackField.X ][ blackField.Y ].directions[ EAST ];

	// SOUTH's field NOTH wall is current's field SOUTH wall
	Map[ blackField.X ][ blackField.Y + 1 ].directions[NOTH] = Map[ blackField.X ][ blackField.Y ].directions[ SOUTH ];

	// WEST's field EAST wall is current's field WEST wall
	Map[ blackField.X - 1 ][ blackField.Y ].directions[EAST] = Map[ blackField.X ][ blackField.Y ].directions[ WEST ];

}

uint8_t mapSearchForUnvisited(Vector startPoint, Vector *skip) 
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

	for(uint8_t i=0; i<100; ++i)
	{
		Serial.print("[");
		Serial.print(skip[i].X);Serial.print(", ");Serial.print(skip[i].Y);Serial.print("]  ");
	}
	Serial.println();
		
	// for every direction check if there is an unvisited
	Vector child;
	uint8_t result;

	// NOTH child
	child.X = startPoint.X;
	child.Y = startPoint.Y - 1;
	// no wall in NOTH      &&     not in the skip array
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[NOTH] && !mapFieldInSkip( child, skip ));
	{
		// distance to nearest unvisited
		result = mapSearchForUnvisited( child, skip);
		// if there is an unvisited add 1 distance and return
		if(result>0)
		{
			return(result + 1);
		}
	}
	// EAST child
	child.X = startPoint.X + 1;
	child.Y = startPoint.Y;
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[EAST] && !mapFieldInSkip( child, skip ))
	{
		result = mapSearchForUnvisited( child, skip);
		if(result>0)
		{
			return(result + 1);
		}
	}
	// SOUTH child
	child.X = startPoint.X;
	child.Y = startPoint.Y + 1;
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[SOUTH] && !mapFieldInSkip( child, skip ))
	{
		result = mapSearchForUnvisited( child, skip);
		if(result>0)
		{
			return(result + 1);
		}
	}
	// WEST child
	child.X = startPoint.X - 1;
	child.Y = startPoint.Y;
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[WEST] && !mapFieldInSkip( child, skip ))
	{
		result = mapSearchForUnvisited( child, skip);
		if(result>0)
		{
			return(result + 1);
		}
	}

	// not found any unvisited
	return(0);
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
	Serial.print("distances: ");
	Serial.print(array[0]);Serial.print(" ");
	Serial.print(array[1]);Serial.print(" ");
	Serial.print(array[2]);Serial.print(" ");
	Serial.println(array[3]);

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

	Serial.print("Koordinaten: ");
	Serial.print((*robot_is_at).X);Serial.print(" ");
	Serial.println((*robot_is_at).Y);

	uint8_t distance[4];
	Vector startSearch;
	Vector skip[100];
	skip[0] = *robot_is_at;
	
	/*Serial.print(Map[ robot_is_at.X ][ robot_is_at.Y ].directions[NOTH]);
	Serial.print(Map[ robot_is_at.X ][ robot_is_at.Y ].directions[EAST]);
	Serial.print(Map[ robot_is_at.X ][ robot_is_at.Y ].directions[SOUTH]);
	Serial.println(Map[ robot_is_at.X ][ robot_is_at.Y ].directions[WEST]);*/

	// check closest's unvisited in NOTH
	if(!Map[ (*robot_is_at).X ][ (*robot_is_at).Y ].directions[NOTH])
	{
		startSearch.X = (*robot_is_at).X;
		startSearch.Y = (*robot_is_at).Y - 1;
		distance[NOTH] = mapSearchForUnvisited( startSearch, skip);
	}else{
		distance[NOTH] = 0;
	}

	// check closest's unvisited in EAST
	if(!Map[ (*robot_is_at).X ][ (*robot_is_at).Y ].directions[EAST])
	{
		startSearch.X = (*robot_is_at).X + 1;
		startSearch.Y = (*robot_is_at).Y;
		distance[EAST] = mapSearchForUnvisited( startSearch, skip);
	}else{
		distance[EAST] = 0;
	}

	// check closest's unvisited in SOUTH
	if(!Map[ (*robot_is_at).X ][ (*robot_is_at).Y ].directions[SOUTH])
	{
		startSearch.X = (*robot_is_at).X;
		startSearch.Y = (*robot_is_at).Y + 1;
		distance[SOUTH] = mapSearchForUnvisited( startSearch, skip);
	}else{
		distance[SOUTH] = 0;
	}

	// check closest's unvisited in WEST
	if(!Map[ (*robot_is_at).X ][ (*robot_is_at).Y ].directions[WEST])
	{
		startSearch.X = (*robot_is_at).X - 1;
		startSearch.Y = (*robot_is_at).Y;
		distance[WEST] = mapSearchForUnvisited( startSearch, skip);
	}else{
		distance[WEST] = 0;
	}

	// return the direction with the nearest unvisited
	return(indexofSmallestElement(&distance[0]));
}


