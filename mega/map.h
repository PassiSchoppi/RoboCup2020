#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include "config.h"

struct Field{
	bool directions[4];
	bool visited;
};

void initMap();
void createNewField();
void updateField();
void searchForUnvisited();
void whereToDrive();

#endif MAP_H
