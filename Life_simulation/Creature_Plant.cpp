﻿#pragma once
#include "Creature_Plant.h"



Creature_Plant::Creature_Plant(std::pair<int, int> map_cord, int energy, DIRECTION dir, int age, std::vector<Action*>* brain, unsigned int iter) : Creature(map_cord, energy, dir, age, brain, iter) {
	this->CountPlant++;

	if (brain == nullptr) {
		Creature_Plant::brain_mutation(&this->brain, (rand() % start_max_len_brain) + 1);
	}
	else {
		for (auto& act : *brain)
		{
			act->set_Creature(this);    // пометил как свой
		}
		this->brain = *brain;    // скопировал мозг и хранит как свой
	}
	//this->iter = rand() % this->brain.size();
}
int Creature_Plant::CountPlant = 0;

Creature_Plant::~Creature_Plant() {
	this->CountPlant--;
}

Creature* Creature_Plant::copy(std::pair<int, int> map_cord) {
	std::vector<Action*>* br = copy_brain(this->brain);
	Creature_Plant* tmp = new Creature_Plant(map_cord, this->energy, this->dir, this->age, br);
	delete br;
	return tmp;
}

void Creature_Plant::step()
{
	Creature::make_act();
	//this->energy -= (limit_energy * PosSliderAllLose * this->CountPlant) / (size_map_x * size_map_y * 100);
	this->check_my_live();
}

void Creature_Plant::draw_myself(HDC hdc, std::pair<int, int> cord)
{
	cord.first += size_half_cell; cord.second += size_half_cell;
	SelectObject(hdc, H_Green);
	RoundRect(hdc, cord.first - size_creature_radius, cord.second - size_creature_radius, cord.first + size_creature_radius, cord.second + size_creature_radius, size_creature_radius * 2 - 2, size_creature_radius * 2 - 2);
}

int Creature_Plant::get_type_count()
{
	return Creature_Plant::CountPlant;
}

TYPE_CREATURE Creature_Plant::get_TYPE_CREATURE() {
	return TYPE_CREATURE::PLANT;
}

void Creature_Plant::brain_mutation(std::vector<Action*>* change_brain, unsigned int mut_iter) // мутирует ген номер mut_iter или мозг дорастает до мутируемго гена
{
	if (change_brain->size() > mut_iter) {     // если меняемый ген уже создан
		if (rand() % 2 || !(*change_brain)[mut_iter]->mutation()) {			// возможно поменять часть гена
			delete (*change_brain)[mut_iter];								// если не получилось, то изменить весь ген
			(*change_brain)[mut_iter] = Creature_Plant::get_rand_Action(this, change_brain->size());
		}
		return;
	}

	while (mut_iter >= change_brain->size()) {
		change_brain->push_back(Creature_Plant::get_rand_Action(this, mut_iter));
	}
	//for (auto& act : this->brain)   // чтобы с большим шансом на новые гены ссылалсь
	//{
	//	if (rand() % 2) {
	//		act->mutation();
	//	}
	//}
}


Action* Creature_Plant::get_rand_Action(Creature* creature, unsigned int max_iter)
{
	switch (rand() % (TYPE_ACTION::CHANGE_ITER))  // случайное действие с номером до CHANGE_ITER не включительно
	{
	case TYPE_ACTION::GO:
		return new Creature_Plant::Action_go(static_cast<Creature_Plant*>(creature));
	case TYPE_ACTION::EAT:
		return new Creature_Plant::Action_eat(static_cast<Creature_Plant*>(creature));
	case TYPE_ACTION::MULTIPLY:
		return new Creature_Plant::Action_multiply(static_cast<Creature_Plant*>(creature));
	case TYPE_ACTION::TURN:
		return new Creature_Plant::Action_turn(static_cast<Creature_Plant*>(creature), DIRECTION(rand() % 3 - 3));
	case TYPE_ACTION::CONDITION_BY_TYPE_CREATURE:
		return new Creature_Plant::Action_condition_by_TYPE_CREATURE(static_cast<Creature_Plant*>(creature), DIRECTION(rand() % 4 - 4), rand() % max_iter, rand() % max_iter, TYPE_CREATURE(rand() % 4));
	case TYPE_ACTION::CONDITION_BY_CELL_ENERGY:
	{
		int tmp = (rand() % 5);
		return new Creature_Plant::Action_condition_by_Cell_energy(static_cast<Creature_Plant*>(creature), DIRECTION(tmp == 4 ? 4 : tmp - 4), rand() % max_iter, rand() % max_iter, rand() % limit_energy);
	}
	case TYPE_ACTION::CONDITION_BY_CREATURE_ENERGY:
	{
		int tmp = (rand() % 5);
		return new Creature_Plant::Action_condition_by_Creature_energy(static_cast<Creature_Plant*>(creature), DIRECTION(tmp == 4 ? 4 : tmp - 4), rand() % max_iter, rand() % max_iter, rand() % limit_energy);
	}
	//case TYPE_ACTION::CHANGE_ITER:
	//	return new Creature_Plant::Action_change_iter(static_cast<Creature_Plant*>(creature), rand() % max_iter);
	//	break;
	default:
		throw;
	}
}
