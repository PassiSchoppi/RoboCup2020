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
	bool isBlack = false;
	uint8_t distanceToUnvisited;
};


uint8_t mapDirectionToCompas(uint8_t directionI);
uint8_t mapCompasToDirection(uint8_t compasI);
uint8_t indexofSmallestElement(uint8_t array[4]);
void mapInit();
void mapUpdateField();
void mapMoveTo(uint8_t directionToGo);
void mapBlackFieldFront(uint8_t *robot_is_facing, Vector *robot_is_at);
bool mapFieldInSkip(Vector field, Vector *skip);
uint8_t mapSearchForUnvisited(Vector startPoint, Vector *skip);
uint8_t mapWhereToDrive();
void mapDisplay();

#endif
