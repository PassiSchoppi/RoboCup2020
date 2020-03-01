#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include "config.h"
#include "sensor.h"
#include "wall.h"

struct Vector
{
	uint8_t X;
	uint8_t Y;
};

struct Field
{
	bool directions[4] = {1, 1, 1, 1};
	bool visited;
	bool isSilver;
};

void mapInit();
// void mapNewField(int x, int y, int north, int east, int south, int west);
void mapUpdateField();
void mapBlackFieldFront();
bool mapFieldInSkip(Vector field, Vector skip[40]);
uint8_t mapSearchForUnvisited(Vector startPoint, Vector skip[40]);
uint8_t mapWhereToDrive();

#endif MAP_H
