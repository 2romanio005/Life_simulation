#pragma once
#include "Creature_Herbivore.h"

Creature_Herbivore::Action_go::Action_go(Creature_Herbivore* creature) : Action_go_global(creature)
{
}

bool Creature_Herbivore::Action_go::use()
{
	std::pair<int, int> next = near_cell_cord(static_cast<Creature_Herbivore*>(this->creature)->map_cord, static_cast<Creature_Herbivore*>(this->creature)->dir);

	if (map[next.first][next.second].get_TYPE_CREATURE() == TYPE_CREATURE::Void) {
		map[next.first][next.second].swap_Creapure(&map[static_cast<Creature_Herbivore*>(this->creature)->map_cord.first][static_cast<Creature_Herbivore*>(this->creature)->map_cord.second]);
		static_cast<Creature_Herbivore*>(this->creature)->map_cord = next;
	}

	static_cast<Creature_Herbivore*>(this->creature)->next_iter();
	return true;
}

Action* Creature_Herbivore::Action_go::copy()
{
	return new Action_go(static_cast<Creature_Herbivore*>(this->creature));
}


Creature_Herbivore::Action_eat::Action_eat(Creature_Herbivore* creature) : Action_eat_global(creature)
{
}

bool Creature_Herbivore::Action_eat::use()
{
	Cell* next_cell = get_Cell_by_map_cord(near_cell_cord(static_cast<Creature_Herbivore*>(this->creature)->map_cord, static_cast<Creature_Herbivore*>(this->creature)->dir));

	if (next_cell->get_TYPE_CREATURE() != TYPE_CREATURE::Void) {
		int out = next_cell->get_Creature_energy();
		next_cell->set_Creature();

		next_cell->change_free_energy((out * PosSliderRedLeave) / 100);
		static_cast<Creature_Herbivore*>(this->creature)->energy += (out * PosSliderRedEat) / 100;
	}

	static_cast<Creature_Herbivore*>(this->creature)->next_iter();
	return true;
}

Action* Creature_Herbivore::Action_eat::copy()
{
	return new Action_eat(static_cast<Creature_Herbivore*>(this->creature));
}


Creature_Herbivore::Action_multiply::Action_multiply(Creature_Herbivore* creature) : Action_multiply_global(creature)
{
}

bool Creature_Herbivore::Action_multiply::use()
{
	if (static_cast<Creature_Herbivore*>(this->creature)->energy >= min_multiply_energy) {
		Cell* near_place;
		if (FlagRandDivision) {
			near_place = &map[rand() % size_map_x][rand() % size_map_y];
		}
		else {
			near_place = get_Cell_by_map_cord(near_cell_cord(static_cast<Creature_Herbivore*>(this->creature)->map_cord, static_cast<Creature_Herbivore*>(this->creature)->dir));
		}

		if (near_place->get_TYPE_CREATURE() == TYPE_CREATURE::Void) {
			static_cast<Creature_Herbivore*>(this->creature)->energy /= 3;

			std::vector<Action*>* br = copy_brain(static_cast<Creature_Herbivore*>(this->creature)->brain);

			if (rand() % 100 < mut_chence) {    // мутация
				int mut_iter = rand() % (static_cast<Creature_Herbivore*>(this->creature)->brain.size() + 1);
				static_cast<Creature_Herbivore*>(this->creature)->brain_mutation(min(mut_iter, max_brain_size), br);
			}

			near_place->set_Creature(new Creature_Herbivore(near_place->get_map_cord(), static_cast<Creature_Herbivore*>(this->creature)->energy, DIRECTION(rand() % 4), 0, br));
			delete br;
		}
	}

	static_cast<Creature_Herbivore*>(this->creature)->next_iter();
	return true;
}

Action* Creature_Herbivore::Action_multiply::copy()
{
	return new Action_multiply(static_cast<Creature_Herbivore*>(this->creature));
}


Creature_Herbivore::Action_turn::Action_turn(Creature_Herbivore* creature, DIRECTION to_dir) : Action_turn_global(creature, to_dir)
{
}

bool Creature_Herbivore::Action_turn::use()
{
	static_cast<Creature_Herbivore*>(this->creature)->dir = turn(static_cast<Creature_Herbivore*>(this->creature)->dir, this->to_dir);

	static_cast<Creature_Herbivore*>(this->creature)->next_iter();
	return false;
}

Action* Creature_Herbivore::Action_turn::copy()
{
	return new Action_turn(static_cast<Creature_Herbivore*>(this->creature), this->to_dir);
}


Creature_Herbivore::Action_condition_by_TYPE_CREATURE::Action_condition_by_TYPE_CREATURE(Creature_Herbivore* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, TYPE_CREATURE type_creature) : Action_condition_by_TYPE_CREATURE_global(creature, to_dir, true_iter, false_iter, type_creature)
{
}

bool Creature_Herbivore::Action_condition_by_TYPE_CREATURE::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(static_cast<Creature_Herbivore*>(this->creature)->map_cord, turn(static_cast<Creature_Herbivore*>(this->creature)->dir, this->to_dir)))->get_TYPE_CREATURE() == this->type_creature) {
		static_cast<Creature_Herbivore*>(this->creature)->iter = this->true_iter;
	}
	else {
		static_cast<Creature_Herbivore*>(this->creature)->iter = this->false_iter;
	}

	return false;
}

Action* Creature_Herbivore::Action_condition_by_TYPE_CREATURE::copy()
{
	return new Action_condition_by_TYPE_CREATURE(static_cast<Creature_Herbivore*>(this->creature), this->to_dir, this->true_iter, this->false_iter, this->type_creature);
}


Creature_Herbivore::Action_condition_by_Cell::Action_condition_by_Cell(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit) : Action_condition_by_Cell_global(creature, to_dir, true_iter, false_iter, limit)
{
}

bool Creature_Herbivore::Action_condition_by_Cell::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(static_cast<Creature_Herbivore*>(this->creature)->map_cord, this->to_dir == DIRECTION::UNDER ? DIRECTION::UNDER : turn(static_cast<Creature_Herbivore*>(this->creature)->dir, this->to_dir)))->get_free_energy() >= this->limit) {
		static_cast<Creature_Herbivore*>(this->creature)->iter = this->true_iter;
	}
	else {
		static_cast<Creature_Herbivore*>(this->creature)->iter = this->false_iter;
	}

	return false;
}

Action* Creature_Herbivore::Action_condition_by_Cell::copy()
{
	return new Action_condition_by_Cell(static_cast<Creature_Herbivore*>(this->creature), this->to_dir, this->true_iter, this->false_iter, this->limit);
}


Creature_Herbivore::Action_change_iter::Action_change_iter(Creature_Herbivore* creature, unsigned int iter) : Action_change_iter_global(creature, iter)
{
}

bool Creature_Herbivore::Action_change_iter::use()
{
	static_cast<Creature_Herbivore*>(this->creature)->iter = this->iter;

	return false;
}

Action* Creature_Herbivore::Action_change_iter::copy()
{
	return new Action_change_iter(static_cast<Creature_Herbivore*>(this->creature), this->iter);
}


