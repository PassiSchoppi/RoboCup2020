#include "map.h"

Field map[100][100];
int robot_is_at_x = 50;
int robot_is_at_y = 50;
uint8_t robot_is_facing = NORTH;

void mapInit() 
{
	
}

void mapNewField(int x, int y, int north, int east, int south, int west) 
{
	
}

void mapUpdateField() 
{
	uint8_t localSensorData[15];
	uint8_t directionsInOrder[4];
	sensorRead(&localSensorData[0]);
	
	map[robot_is_at_x, robot_is_at_y].visited = true;
	map[robot_is_at_x, robot_is_at_y].seen = true;
	
	switch(robot_is_facing)
	{
		case 0:
			directionsInOrder[4] = {1, 2, 3, 4};
			break;
		
		case 1:
			directionsInOrder[4] = {2, 3, 4, 1};
			break;
				
		case 2:
			directionsInOrder[4] = {3, 4, 1, 2};
			break;
				
		case 3:
			directionsInOrder[4] = {4, 1, 2, 3};
			break;
	}
	
	for(uint8_t i = 0; i < 4; ++i)
	{
		map[robot_is_at_x][robot_is_at_y].directions[i] = wallExists( directionsInOrder[i], &localSensorData[0]);
		
		if(map[robot_is_at_x][robot_is_at_y].directions[i] && 
	}
}

void mapSearchForUnvisited() 
{
	
}

void mapWhereToDrive() 
{
	
}

