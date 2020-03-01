#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include "config.h"
#include "sensor.h"

struct Field{
	bool directions[4];
	bool visited;
	bool seen;
};

void mapInit();
void mapNewField(int x, int y, int north, int east, int south, int west);
void mapUpdateField();
void mapSearchForUnvisited();
void mapWhereToDrive();

#endif MAP_H
