#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include "config.h"
#include "sensor.h"
#include "wall.h"

struct Vector
{
	uint8_t X = 0;
	uint8_t Y = 0;
};

struct Field
{
	bool directions[4] = {1, 1, 1, 1};
	bool visited = false;
	bool isSilver = false;
};



void mapInit();
// void mapNewField(int x, int y, int north, int east, int south, int west);
void mapUpdateField(uint8_t *robot_is_facing, Vector *robot_is_at);
void mapBlackFieldFront(uint8_t *robot_is_facing, Vector robot_is_at);
bool mapFieldInSkip(Vector field, Vector *skip);
uint8_t mapSearchForUnvisited(Vector startPoint, Vector *skip);
uint8_t mapWhereToDrive(Vector *robot_is_at);

#endif
