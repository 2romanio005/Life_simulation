#pragma once
#include "Definition.h"

enum TYPE_CREATURE
{
	Plant,
	Herbivore,
	Scavenger,

	Void
};

enum TYPE_ACTION
{
	GO,
	EAT,
	MULTIPLY,
	TURN,
	CONDITION_BY_TYPE_CREATURE,
	CONDITION_BY_CELL,
	CHANGE_ITER   // не испльзуется
};

enum DIRECTION
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,

	UNDER = 4,

	to_FORWARD = -4,
	to_RIGHT = -3,
	to_LEFT = -1,
	to_BACK = -2
};
