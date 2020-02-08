#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include "config.h"

struct Field{
	bool directions[4];
	bool visited;
};

void mapInit();
void mapNewField();
void mapUpdateField();
void mapSearchForUnvisited();
void mapWhereToDrive();

#endif MAP_H
