#pragma once
#include "Creature_Herbivore.h"

Creature_Herbivore::Creature_Herbivore(std::pair<int, int> map_cord, int energy, DIRECTION dir, int age, std::vector<Action*>* brain, unsigned int iter) : Creature(map_cord, energy, dir, age, brain, iter) {
	this->CountHarbivore++;
}
int Creature_Herbivore::CountHarbivore = 0;

Creature_Herbivore::~Creature_Herbivore() {
	this->CountHarbivore--;
}

void Creature_Herbivore::step()
{
	Creature::step();
	this->energy -= (limit_energy * PosSliderAllLose * this->CountHarbivore) / (size_map_x * size_map_y * 100);
	this->check_my_live();
}

Creature* Creature_Herbivore::copy(std::pair<int, int> map_cord) {
	std::vector<Action*>* br = copy_brain(this->brain);
	return new Creature_Herbivore(map_cord, this->energy, this->dir, this->age, copy_brain(this->brain));
	delete br;
}

void Creature_Herbivore::draw_myself(HDC hdc, std::pair<int, int> cord)
{
	int r = int(size_cell * 0.4);
	cord.first += size_half_cell; cord.second += size_half_cell;
	SelectObject(hdc, H_Red);
	RoundRect(hdc, cord.first - r, cord.second - r, cord.first + r, cord.second + r, r * 2, r * 2);
}

int Creature_Herbivore::get_type_count()
{
	return Creature_Herbivore::CountHarbivore;
}

TYPE_CREATURE Creature_Herbivore::get_TYPE_CREATURE() {
	return TYPE_CREATURE::Herbivore;
}


Action* Creature_Herbivore::get_rand_Action(Creature* creature, unsigned int max_iter)
{
	switch (rand() % (TYPE_ACTION::CHANGE_ITER))  // случайное действие с номером до CHANGE_ITER не включительно
	{
	case TYPE_ACTION::GO:
		return new Creature_Herbivore::Action_go(static_cast<Creature_Herbivore*>(creature));
	case TYPE_ACTION::EAT:
		return new Creature_Herbivore::Action_eat(static_cast<Creature_Herbivore*>(creature));
	case TYPE_ACTION::MULTIPLY:
		return new Creature_Herbivore::Action_multiply(static_cast<Creature_Herbivore*>(creature));
	case TYPE_ACTION::TURN:
		return new Creature_Herbivore::Action_turn(static_cast<Creature_Herbivore*>(creature), DIRECTION(rand() % 3 - 3));
	case TYPE_ACTION::CONDITION_BY_TYPE_CREATURE:
		return new Creature_Herbivore::Action_condition_by_TYPE_CREATURE(static_cast<Creature_Herbivore*>(creature), DIRECTION(rand() % 4 - 4), rand() % max_iter, rand() % max_iter, TYPE_CREATURE(rand() % 4));
	case TYPE_ACTION::CONDITION_BY_CELL:
	{
		int tmp = (rand() % 5);
		return new Creature_Herbivore::Action_condition_by_Cell(static_cast<Creature_Herbivore*>(creature), DIRECTION(tmp == 4 ? 4 : tmp - 4), rand() % max_iter, rand() % max_iter, rand() % limit_energy);
	}
	//case TYPE_ACTION::CHANGE_ITER:
	//	return new Creature_Herbivore::Action_change_iter(static_cast<Creature_Herbivore*>(creature), rand() % max_iter);
	//	break;
	default:
		throw;
	}
}
