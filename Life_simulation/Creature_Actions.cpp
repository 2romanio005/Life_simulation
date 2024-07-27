#pragma once
#include "Creatures.h"

Creature::Action_go_global::Action_go_global(Creature* creature) : Action(creature)
{
}

std::string* Creature::Action_go_global::draw_myself()
{
	return new std::string[5]
	{
		"Идти",
		"",
		"",
		"",
		""
	};
}

TYPE_ACTION Creature::Action_go_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::GO;
}



Creature::Action_eat_global::Action_eat_global(Creature* creature) : Action(creature)
{
}

std::string* Creature::Action_eat_global::draw_myself()
{
	return new std::string[5]
	{
		"Есть",
		"",
		"",
		"",
		""
	};
}

TYPE_ACTION Creature::Action_eat_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::EAT;
}



Creature::Action_multiply_global::Action_multiply_global(Creature* creature) : Action(creature)
{
}

std::string* Creature::Action_multiply_global::draw_myself()
{
	return new std::string[5]
	{
		"Размн",
		"",
		"",
		"",
		""
	};
}

TYPE_ACTION Creature::Action_multiply_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::MULTIPLY;
}



Creature::Action_turn_global::Action_turn_global(Creature* creature, DIRECTION to_dir) : Action(creature)
{
	this->to_dir = to_dir;
}

bool Creature::Action_turn_global::use()
{
	this->creature->dir = turn(this->creature->dir, this->to_dir);

	this->creature->next_iter();
	return false;
}

bool Creature::Action_turn_global::mutation()
{
	this->to_dir = DIRECTION(rand() % 3 - 3);
	return true;
}

std::string* Creature::Action_turn_global::draw_myself()
{
	return new std::string[5]
	{
		"Повoрот",
		string_by_dir_for_turn(this->to_dir),
		"",
		"",
		""
	};
}

void Creature::Action_turn_global::write_myself(std::string* out)
{
	*out +=
		std::to_string(this->get_TYPE_ACTION())
		+ ';' + std::to_string(this->to_dir)
		+ ";0;0;0;";
}

TYPE_ACTION Creature::Action_turn_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::TURN;
}



Creature::Action_condition_by_TYPE_CREATURE_global::Action_condition_by_TYPE_CREATURE_global(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, TYPE_CREATURE type_creature) : Action(creature)
{
	this->to_dir = to_dir;

	this->true_iter = true_iter;
	this->false_iter = false_iter;

	this->type_creature = type_creature;
}

bool Creature::Action_condition_by_TYPE_CREATURE_global::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, turn(this->creature->dir, this->to_dir)))->get_TYPE_CREATURE() == this->type_creature) {
		this->creature->iter = this->true_iter;
	}
	else {
		this->creature->iter = this->false_iter;
	}

	return false;
}

bool Creature::Action_condition_by_TYPE_CREATURE_global::mutation()
{
	switch (rand() % 4)
	{
	case 0:
		this->true_iter = rand() % this->creature->brain.size();
		break;
	case 1:
		this->false_iter = rand() % this->creature->brain.size();
		break;
	case 2:
		this->to_dir = DIRECTION(rand() % 4 - 4);
		break;
	case 3:
		this->type_creature = TYPE_CREATURE(rand() % (TYPE_CREATURE::Void + 1));
		break;
	}

	return true;
}

std::string* Creature::Action_condition_by_TYPE_CREATURE_global::draw_myself()
{
	return new std::string[5]
	{
		"Условие",
		string_by_dir_for_condition(this->to_dir),
		string_by_type_creature(this->type_creature),
		std::to_string(this->true_iter),
		std::to_string(this->false_iter)
	};
}

void Creature::Action_condition_by_TYPE_CREATURE_global::write_myself(std::string* out)
{
	*out +=
		std::to_string(this->get_TYPE_ACTION())
		+ ';' + std::to_string(this->to_dir)
		+ ';' + std::to_string(this->type_creature)
		+ ';' + std::to_string(this->true_iter)
		+ ';' + std::to_string(this->false_iter)
		+ ';';
}

TYPE_ACTION Creature::Action_condition_by_TYPE_CREATURE_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::CONDITION_BY_TYPE_CREATURE;
}




Creature:: Action_condition_by_Cell_energy_global:: Action_condition_by_Cell_energy_global(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit) : Action(creature)
{
	this->to_dir = to_dir;

	this->true_iter = true_iter;
	this->false_iter = false_iter;

	this->limit = limit;
	//this->cond = cond;
}

bool Creature::Action_condition_by_Cell_energy_global::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, this->to_dir == DIRECTION::UNDER ? DIRECTION::UNDER : turn(this->creature->dir, this->to_dir)))->get_free_energy() >= this->limit) {
		this->creature->iter = this->true_iter;
	}
	else {
		this->creature->iter = this->false_iter;
	}

	return false;
}

bool Creature:: Action_condition_by_Cell_energy_global::mutation()
{
	switch (rand() % 4)
	{
	case 0:
		this->true_iter = rand() % this->creature->brain.size();
		break;
	case 1:
		this->false_iter = rand() % this->creature->brain.size();
		break;
	case 2:
	{
		int tmp = rand() % 5;
		this->to_dir = DIRECTION(tmp == 4 ? 4 : (tmp - 4));
		break;
	}
	case 3:
		this->limit = rand() % limit_energy;
		break;
	}
	return true;
}

std::string* Creature:: Action_condition_by_Cell_energy_global::draw_myself()
{
	return new std::string[5]
	{
		"На клетке",
		string_by_dir_for_condition(this->to_dir),
		std::to_string(this->limit),
		std::to_string(this->true_iter),
		std::to_string(this->false_iter)
	};
}

void Creature:: Action_condition_by_Cell_energy_global::write_myself(std::string* out)
{
	*out +=
		std::to_string(this->get_TYPE_ACTION())
		+ ';' + std::to_string(this->to_dir)
		+ ';' + std::to_string(this->limit)
		+ ';' + std::to_string(this->true_iter)
		+ ';' + std::to_string(this->false_iter)
		+ ';';
}

TYPE_ACTION Creature:: Action_condition_by_Cell_energy_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::CONDITION_BY_CELL_ENERGY;
}




Creature::Action_condition_by_Creature_energy_global::Action_condition_by_Creature_energy_global(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit) : Action(creature)
{
	this->to_dir = to_dir;

	this->true_iter = true_iter;
	this->false_iter = false_iter;

	this->limit = limit;
}

bool Creature::Action_condition_by_Creature_energy_global::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, this->to_dir == DIRECTION::UNDER ? DIRECTION::UNDER : turn(this->creature->dir, this->to_dir)))->get_Creature_energy() >= this->limit) {
		this->creature->iter = this->true_iter;
	}
	else {
		this->creature->iter = this->false_iter;
	}

	return false;
}

bool Creature::Action_condition_by_Creature_energy_global::mutation()
{
	switch (rand() % 4)
	{
	case 0:
		this->true_iter = rand() % this->creature->brain.size();
		break;
	case 1:
		this->false_iter = rand() % this->creature->brain.size();
		break;
	case 2:
	{
		int tmp = rand() % 5;
		this->to_dir = DIRECTION(tmp == 4 ? 4 : (tmp - 4));
		break;
	}
	case 3:
		this->limit = rand() % limit_energy;
		break;
	}

	return true;
}

std::string* Creature::Action_condition_by_Creature_energy_global::draw_myself()
{
	return new std::string[5]
	{
		"У существа",
		string_by_dir_for_condition(this->to_dir),
		std::to_string(this->limit),
		std::to_string(this->true_iter),
		std::to_string(this->false_iter)
	};
}

void Creature::Action_condition_by_Creature_energy_global::write_myself(std::string* out)
{
	*out +=
		std::to_string(this->get_TYPE_ACTION())
		+ ';' + std::to_string(this->to_dir)
		+ ';' + std::to_string(this->limit)
		+ ';' + std::to_string(this->true_iter)
		+ ';' + std::to_string(this->false_iter)
		+ ';';
}

TYPE_ACTION Creature::Action_condition_by_Creature_energy_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::CONDITION_BY_CREATURE_ENERGY;
}





Creature::Action_change_iter_global::Action_change_iter_global(Creature* creature, unsigned int iter) : Action(creature)
{
	this->iter = iter;
}

bool Creature::Action_change_iter_global::mutation()
{
	this->iter = rand() % this->creature->brain.size();
	return true;
}

std::string* Creature::Action_change_iter_global::draw_myself()
{
	return new std::string[5]
	{
		"Переход",
		"",
		"",
		std::to_string(this->iter),
		std::to_string(this->iter)
	};
}

void Creature::Action_change_iter_global::write_myself(std::string* out)
{
	*out +=
		std::to_string(this->get_TYPE_ACTION())
		+ ";0;0"
		+ ';' + std::to_string(this->iter)
		+ ';' + std::to_string(this->iter)
		+ ';';
}

TYPE_ACTION Creature::Action_change_iter_global::get_TYPE_ACTION()
{
	return TYPE_ACTION::CHANGE_ITER;
}

























