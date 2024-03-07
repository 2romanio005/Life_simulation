#pragma once
#include "Creature_Plant.h"

Creature_Plant::Action_go::Action_go(Creature_Plant* creature) : Action_go_global(creature)
{
}

bool Creature_Plant::Action_go::use()
{
	std::pair<int, int> next = near_cell_cord(static_cast<Creature_Plant*>(this->creature)->map_cord, static_cast<Creature_Plant*>(this->creature)->dir);

	if (map[next.first][next.second].get_TYPE_CREATURE() == TYPE_CREATURE::Void) {
		map[next.first][next.second].swap_Creapure(&map[static_cast<Creature_Plant*>(this->creature)->map_cord.first][static_cast<Creature_Plant*>(this->creature)->map_cord.second]);
		static_cast<Creature_Plant*>(this->creature)->map_cord = next;
	}

	static_cast<Creature_Plant*>(this->creature)->next_iter();
	return true;
}

Action* Creature_Plant::Action_go::copy()
{
	return new Action_go(static_cast<Creature_Plant*>(this->creature));
}


Creature_Plant::Action_eat::Action_eat(Creature_Plant* creature) : Action_eat_global(creature)
{
}

bool Creature_Plant::Action_eat::use()
{	
	int tmp = limit_energy - static_cast<Creature_Plant*>(this->creature)->get_under_me()->get_free_energy() * (100 - PosSliderGreenEat);
	if (tmp < 0) tmp = 0;

	static_cast<Creature_Plant*>(this->creature)->energy += tmp;

	static_cast<Creature_Plant*>(this->creature)->next_iter();
	return true;
}

Action* Creature_Plant::Action_eat::copy()
{
	return new Action_eat(static_cast<Creature_Plant*>(this->creature));
}


Creature_Plant::Action_multiply::Action_multiply(Creature_Plant* creature) : Action_multiply_global(creature)
{
}

bool Creature_Plant::Action_multiply::use()
{
	if (static_cast<Creature_Plant*>(this->creature)->energy >= min_multiply_energy) {
		Cell* near_place;
		if (FlagRandDivision) {
			near_place = &map[rand() % size_map_x][rand() % size_map_y];
		}
		else {
			near_place = get_Cell_by_map_cord(near_cell_cord(static_cast<Creature_Plant*>(this->creature)->map_cord, static_cast<Creature_Plant*>(this->creature)->dir));
		}

		if (near_place->get_TYPE_CREATURE() == TYPE_CREATURE::Void) {
			static_cast<Creature_Plant*>(this->creature)->energy /= 3;

			std::vector<Action*>* br = copy_brain(static_cast<Creature_Plant*>(this->creature)->brain);

			if (rand() % 100 < mut_chence) {    // мутация
				int mut_iter = rand() % (static_cast<Creature_Plant*>(this->creature)->brain.size() + 1);
				static_cast<Creature_Plant*>(this->creature)->brain_mutation(min(mut_iter, max_brain_size), br);
			}

			//Creature* cr = nullptr;
			//switch (((rand() % 100) < mut_type_chence) ? (rand() % 3) : static_cast<Creature_Plant*>(this->creature)->get_TYPE_CREATURE())
			//{
			//case TYPE_CREATURE::Plant:
			//	cr = new Creature_Plant(near_place->get_map_cord(), static_cast<Creature_Plant*>(this->creature)->energy, DIRECTION(rand() % 4), 0, br);
			//	break;
			//case TYPE_CREATURE::Herbivore:
			//	cr = new Creature_Herbivore(near_place->get_map_cord(), static_cast<Creature_Plant*>(this->creature)->energy, DIRECTION(rand() % 4), 0, br);
			//	break;
			//case TYPE_CREATURE::Scavenger:
			//	cr = new Creature_Scavenger(near_place->get_map_cord(), static_cast<Creature_Plant*>(this->creature)->energy, DIRECTION(rand() % 4), 0, br);
			//	break;
			//default:
			//	throw;
			//	break;
			//}
			near_place->set_Creature(new Creature_Plant(near_place->get_map_cord(), static_cast<Creature_Plant*>(this->creature)->energy, DIRECTION(rand() % 4), 0, br));
			delete br;
		}
	}

	static_cast<Creature_Plant*>(this->creature)->next_iter();
	return true;
}

Action* Creature_Plant::Action_multiply::copy()
{
	return new Action_multiply(static_cast<Creature_Plant*>(this->creature));
}


Creature_Plant::Action_turn::Action_turn(Creature_Plant* creature, DIRECTION to_dir) : Action_turn_global(creature, to_dir)
{
}

bool Creature_Plant::Action_turn::use()
{
	static_cast<Creature_Plant*>(this->creature)->dir = turn(static_cast<Creature_Plant*>(this->creature)->dir, this->to_dir);

	static_cast<Creature_Plant*>(this->creature)->next_iter();
	return false;
}

Action* Creature_Plant::Action_turn::copy()
{
	return new Action_turn(static_cast<Creature_Plant*>(this->creature), this->to_dir);
}


Creature_Plant::Action_condition_by_TYPE_CREATURE::Action_condition_by_TYPE_CREATURE(Creature_Plant* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, TYPE_CREATURE type_creature) : Action_condition_by_TYPE_CREATURE_global(creature, to_dir, true_iter, false_iter, type_creature)
{
}

bool Creature_Plant::Action_condition_by_TYPE_CREATURE::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(static_cast<Creature_Plant*>(this->creature)->map_cord, turn(static_cast<Creature_Plant*>(this->creature)->dir, this->to_dir)))->get_TYPE_CREATURE() == this->type_creature) {
		static_cast<Creature_Plant*>(this->creature)->iter = this->true_iter;
	}
	else {
		static_cast<Creature_Plant*>(this->creature)->iter = this->false_iter;
	}

	return false;
}

Action* Creature_Plant::Action_condition_by_TYPE_CREATURE::copy()
{
	return new Action_condition_by_TYPE_CREATURE(static_cast<Creature_Plant*>(this->creature), this->to_dir, this->true_iter, this->false_iter, this->type_creature);
}


Creature_Plant::Action_condition_by_Cell::Action_condition_by_Cell(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit) : Action_condition_by_Cell_global(creature, to_dir, true_iter, false_iter, limit)
{
}

bool Creature_Plant::Action_condition_by_Cell::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(static_cast<Creature_Plant*>(this->creature)->map_cord, this->to_dir == DIRECTION::UNDER ? DIRECTION::UNDER : turn(static_cast<Creature_Plant*>(this->creature)->dir, this->to_dir)))->get_free_energy() >= this->limit) {
		static_cast<Creature_Plant*>(this->creature)->iter = this->true_iter;
	}
	else {
		static_cast<Creature_Plant*>(this->creature)->iter = this->false_iter;
	}

	return false;
}

Action* Creature_Plant::Action_condition_by_Cell::copy()
{
	return new Action_condition_by_Cell(static_cast<Creature_Plant*>(this->creature), this->to_dir, this->true_iter, this->false_iter, this->limit);
}


Creature_Plant::Action_change_iter::Action_change_iter(Creature_Plant* creature, unsigned int iter) : Action_change_iter_global(creature, iter)
{
}

bool Creature_Plant::Action_change_iter::use()
{
	static_cast<Creature_Plant*>(this->creature)->iter = this->iter;

	return false;
}

Action* Creature_Plant::Action_change_iter::copy()
{
	return new Action_change_iter(static_cast<Creature_Plant*>(this->creature), this->iter);
}


