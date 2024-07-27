#pragma once

enum TYPE_CREATURE
{
	PLANT,
	HERBIVORE,
	SCAVENGER,

	Void    // закреплено как последнее для % 
};

enum TYPE_ACTION
{
	GO,
	EAT,
	MULTIPLY,
	TURN,
	CONDITION_BY_TYPE_CREATURE,
	CONDITION_BY_CELL_ENERGY,
	CONDITION_BY_CREATURE_ENERGY,
	CHANGE_ITER   // не испльзуется // закреплено как последнее для % 
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
