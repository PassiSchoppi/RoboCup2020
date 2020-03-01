#include "map.h"

Field Map[20][20];
Vector robot_is_at;
uint8_t robot_is_facing = NOTH;

void mapInit() 
{
	robot_is_at.X = 10;
	robot_is_at.Y = 10;
}

void mapUpdateField() 
{
	uint8_t localSensorData[15];
	uint8_t directionsInOrder[4];
	sensorRead(&localSensorData[0]);
	
	// set current field to seen and visited
	Map[robot_is_at.X][robot_is_at.Y].visited = true;
	
	// link direction and pole
	switch(robot_is_facing)
	{
		case NOTH:
			directionsInOrder[FRONT] = NOTH;
			directionsInOrder[RIGHT] = EAST;
			directionsInOrder[BACK] = SOUTH;
			directionsInOrder[LEFT] = WEST;
			break;
		
		case EAST:
			directionsInOrder[FRONT] = EAST;
			directionsInOrder[RIGHT] = SOUTH;
			directionsInOrder[BACK] = WEST;
			directionsInOrder[LEFT] = NOTH;
			break;
				
		case SOUTH:
			directionsInOrder[FRONT] = SOUTH;
			directionsInOrder[RIGHT] = WEST;
			directionsInOrder[BACK] = NOTH;
			directionsInOrder[LEFT] = EAST;
			break;
				
		case WEST:
			directionsInOrder[FRONT] = WEST;
			directionsInOrder[RIGHT] = NOTH;
			directionsInOrder[BACK] = EAST;
			directionsInOrder[LEFT] = SOUTH;
			break;
	}
	
	// write walls to current field
	for(uint8_t i = 0; i < 4; ++i)
	{
		Map[robot_is_at.Y][robot_is_at.Y].directions[i] = wallExists( directionsInOrder[i], &localSensorData[0]);
	}

	// write fields to surrounding fields
	// NOTH's field SOUTH wall is current's field NOTH wall
	Map[robot_is_at.X][robot_is_at.Y - 1].directions[SOUTH] = Map[robot_is_at.X][robot_is_at.Y].directions[NOTH];

	// EAST field's west wall is current's field EAST wall
	Map[robot_is_at.X + 1][robot_is_at.Y].directions[WEST] = Map[robot_is_at.X][robot_is_at.Y].directions[EAST];
	
	// SOUTH's field NOTH wall is current's field SOUTH wall
	Map[robot_is_at.X][robot_is_at.Y + 1].directions[NOTH] = Map[robot_is_at.X][robot_is_at.Y].directions[SOUTH];
	
	// WEST's field EAST wall is current's field WEST wall
	Map[robot_is_at.X - 1][robot_is_at.Y].directions[EAST] = Map[robot_is_at.X][robot_is_at.Y].directions[WEST];
}



void mapBlackFieldFront()
{
	Vector blackField;
	// link direction and pole
	switch(robot_is_facing)
	{
		case NOTH:
			blackField.X = robot_is_at.X;
			blackField.Y = robot_is_at.Y - 1;
			break;

		case EAST:
			blackField.X = robot_is_at.X + 1;
			blackField.Y = robot_is_at.Y;
			break;
				
		case SOUTH:
			blackField.X = robot_is_at.X;
			blackField.Y = robot_is_at.Y + 1;
			break;
				
		case WEST:
			blackField.X = robot_is_at.X - 1;
			blackField.Y = robot_is_at.Y;
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

uint8_t mapSearchForUnvisited(Vector startPoint, Vector skip[40]) 
{
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
	skip[i].X = startPoint.X;
	skip[i].Y = startPoint.Y;
	
	// for every direction
	Vector child;
	uint8_t result;
	// NOTH chiled
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[NOTH] && !mapFieldInSkip( startPoint, skip ));
	{
		child.X = startPoint.X;
		child.Y = startPoint.Y - 1;
		result = mapSearchForUnvisited(child, skip);
		if(result)
		{
			return(result + 1);
		}
	}
	// EAST chiled
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[EAST] && !mapFieldInSkip( startPoint, skip ))
	{
		child.X = startPoint.X + 1;
		child.Y = startPoint.Y;
		result = mapSearchForUnvisited(child, skip);
		if(result)
		{
			return(result + 1);
		}
	}
	// SOUTH chiled
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[SOUTH] && !mapFieldInSkip( startPoint, skip ))
	{
		child.X = startPoint.X;
		child.Y = startPoint.Y + 1;
		result = mapSearchForUnvisited(child, skip);
		if(result)
		{
			return(result + 1);
		}
	}
	// WEST chiled
	if(!Map[ startPoint.X ][ startPoint.Y ].directions[WEST] && !mapFieldInSkip( startPoint, skip ))
	{
		child.X = startPoint.X - 1;
		child.Y = startPoint.Y;
		result = mapSearchForUnvisited(child, skip);
		if(result)
		{
			return(result + 1);
		}
	}

	// not found anything
	return(0);
}


bool mapFieldInSkip(Vector field, Vector skip[40])
{
	// checks if field is in skip
	for(uint8_t i=0; i<40; ++i)
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
    uint8_t index = 0;

    for(int i = 1; i < 4; i++)
    {
        if(array[i] < array[index])
            index = i;              
    }
	
	if(array[index]==0)
	{
		return 5;
	}

    return index;
}


uint8_t mapWhereToDrive() 
{
	uint8_t distance[4];
	Vector startSearch;
	Vector skip[40];
	skip[0] = robot_is_at;

	// check closest's unvisited in NOTH
	if(!Map[ robot_is_at.X ][ robot_is_at.Y ].directions[NOTH])
	{
		startSearch.X = robot_is_at.X;
		startSearch.Y = robot_is_at.Y - 1;
		distance[NOTH] = mapSearchForUnvisited( startSearch, skip);
	}

	// check closest's unvisited in EAST
	if(!Map[ robot_is_at.X ][ robot_is_at.Y ].directions[EAST])
	{
		startSearch.X = robot_is_at.X + 1;
		startSearch.Y = robot_is_at.Y;
		distance[EAST] = mapSearchForUnvisited( startSearch, skip);
	}

	// check closest's unvisited in SOUTH
	if(!Map[ robot_is_at.X ][ robot_is_at.Y ].directions[SOUTH])
	{
		startSearch.X = robot_is_at.X;
		startSearch.Y = robot_is_at.Y + 1;
		distance[SOUTH] = mapSearchForUnvisited( startSearch, skip);
	}
	// check closest's unvisited in WEST
	if(!Map[ robot_is_at.X ][ robot_is_at.Y ].directions[WEST])
	{
		startSearch.X = robot_is_at.X - 1;
		startSearch.Y = robot_is_at.Y;
		distance[WEST] = mapSearchForUnvisited( startSearch, skip);
	}

	// return the direction with the nearest unvisited
	return(indexofSmallestElement(&distance[0]));
}


