#pragma once
#include "Actions.h"



Action::Action(Creature* creature)
{
	this->creature = creature;
}

bool Action::mutation()
{
	return false;
}

void Action::write_myself(std::string* out)
{
	*out +=
		std::to_string(this->get_TYPE_ACTION())
		+ ";0;0;0;0;";
}

void Action::set_Creature(Creature* creature)
{
	this->creature = creature;
}

std::pair<std::string, int>* Action::build_draw(){
	std::pair<std::string, int>* out = new std::pair<std::string, int>;
	std::string* sample = this->draw_myself();

	for (int i = 0; i < 5; i++)
	{
		out->second = max(int(sample[i].size()), out->second);
		(*out).first += sample[i] + '\n';
	}

	delete[] sample;
	return out;
}











//bool Action_eat::use()
//{
//	switch (creature->get_TYPE_CREATURE())
//	{
//	case TYPE_CREATURE::PLANT:
//	{
//		//creature->energy += max(limit_energy - (creature->get_under_me()->free_energy += 30), 0);
//		//int tmp = max(400 - this->creature->get_under_me()->get_free_energy(), 0);
//		//int tmp = (limit_energy / 15 - creature->get_under_me()->get_free_energy());
//		//int tmp = (limit_energy - creature->get_under_me()->get_free_energy()) / 7;
//		//int tmp = (limit_energy - creature->get_under_me()->get_free_energy() * 15);
//		int tmp = limit_energy - creature->get_under_me()->get_free_energy() * (100 - PosSliderGreenEat);
//		if (tmp < 0) tmp = 0;
//		this->creature->energy += tmp;
//		//creature->get_under_me()->change_free_energy(1);
//		break;
//	}
//	case TYPE_CREATURE::HERBIVORE:
//	{
		//Cell* next_cell = get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, this->creature->dir));

		//if (next_cell->get_TYPE_CREATURE() != TYPE_CREATURE::Void) {
		//	int out = next_cell->get_Creature_energy();
		//	next_cell->set_Creature();

		//	next_cell->change_free_energy((out * PosSliderRedLeave) / 100);
		//	this->creature->energy +=  (out * PosSliderRedEat) / 100;
		//}
//		break;
//	}
//	case TYPE_CREATURE::SCAVENGER:
//	{
//		//creature->energy += max(creature->get_under_me()->free_energy, 0);
//		//creature->get_under_me()->free_energy = 0;
//
//		//int tmp = min(creature->get_under_me()->get_free_energy(), 400);
//		//int tmp = creature->get_under_me()->get_free_energy() / 6;
//		int tmp = creature->get_under_me()->get_free_energy();
//		if (tmp > 50) {
//			tmp = (tmp * PosSliderBlueEat) / 100;
//		}
//		this->creature->energy += tmp;
//		this->creature->get_under_me()->change_free_energy(-tmp);
//		break;
//	}
//	}
//
//	this->creature->next_iter();
//	return true;
//}
//
//Action* Action_eat::copy()
//{
//	return new Action_eat(this->creature);
//}
//
//
//
//
//
//
//
//bool Action_multiply::use()
//{
//	if (this->creature->energy >= min_multiply_energy) {
//		Cell* near_place;
//		if (FlagRandDivision) {
//			near_place = &map[rand() % size_map_x][rand() % size_map_y];
//		}
//		else {
//			near_place = get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, this->creature->dir));
//		}
//
//		if (near_place->get_TYPE_CREATURE() == TYPE_CREATURE::Void) {
//			this->creature->energy /= 3;
//
//			std::vector<Action*>* br = copy_brain(this->creature->brain);
//
//			if (rand() % 100 < mut_chance) {    // мутация
//				int mut_iter = rand() % (this->creature->brain.size() + 1);
//				this->creature->brain_mutation(min(mut_iter, max_brain_size), br);
//			}
//
//			Creature* cr = nullptr;
//			switch (((rand() % 100) < mut_type_chance) ? (rand() % 3) : this->creature->get_TYPE_CREATURE())
//			{
//			case TYPE_CREATURE::PLANT:
//				cr = new Creature_Plant(near_place->get_map_cord(), this->creature->energy, DIRECTION(rand() % 4), 0, br);
//				break;
//			case TYPE_CREATURE::HERBIVORE:
//				cr = new Creature_Herbivore(near_place->get_map_cord(), this->creature->energy, DIRECTION(rand() % 4), 0, br);
//				break;
//			case TYPE_CREATURE::SCAVENGER:
//				cr = new Creature_Scavenger(near_place->get_map_cord(), this->creature->energy, DIRECTION(rand() % 4), 0, br);
//				break;
//			default:
//				throw;
//				break;
//			}
//			near_place->set_Creature(cr);
//			delete br;
//		}
//	}
//
//	this->creature->next_iter();
//	return true;
//}
//
//Action* Action_multiply::copy()
//{
//	return new Action_multiply(this->creature);
//}
//
//
//
//
//bool Action_turn::use()
//{
//	this->creature->dir = turn(this->creature->dir, this->to_dir);
//
//	this->creature->next_iter();
//	return false;
//}
//
//Action* Action_turn::copy()
//{
//	return new Action_turn(this->creature, this->to_dir);
//}
//
//
//
//
//
//
//bool Action_condition_by_TYPE_CREATURE::use()
//{
//	if (get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, turn(this->creature->dir, this->to_dir)))->get_TYPE_CREATURE() == this->type_creature) {
//		this->creature->iter = this->true_iter;
//	}
//	else {
//		this->creature->iter = this->false_iter;
//	}
//
//	return false;
//}
//
//Action* Action_condition_by_TYPE_CREATURE::copy()
//{
//	return new Action_condition_by_TYPE_CREATURE(this->creature, this->to_dir, this->true_iter, this->false_iter,this->type_creature);
//}
//
//
//
//
//
//bool Action_condition_by_Cell_energy::use()
//{
//	if (get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, this->to_dir == DIRECTION::UNDER ? DIRECTION::UNDER : turn(this->creature->dir, this->to_dir)))->get_free_energy() >= this->limit) {
//		this->creature->iter = this->true_iter;
//	}
//	else {
//		this->creature->iter = this->false_iter;
//	}
//
//	return false;
//}
//
//Action* Action_condition_by_Cell_energy::copy()
//{
//	return new Action_condition_by_Cell_energy(this->creature, this->to_dir, this->true_iter, this->false_iter, this->limit);
//}
//
//
//
//
//bool Action_change_iter::use()
//{
//	this->creature->iter = this->iter;
//
//	return false;
//}
//
//Action* Action_change_iter::copy()
//{
//	return new Action_change_iter(this->creature, this->iter);
//}
//
//
//
//
//





//void Action_look_(Creature* creature)
//{
//	//creature->energy -= use_energy(10);
//
//	creature->see[0].push_back(&map[creature->map_cord.first][(creature->map_cord.second - creature->see[0].size() - 1 + size_map_y) % size_map_y]);
//	creature->see[1].push_back(&map[(creature->map_cord.first + creature->see[1].size() + 1) % size_map_x][creature->map_cord.second]);
//	creature->see[2].push_back(&map[creature->map_cord.first][(creature->map_cord.second + creature->see[2].size() + 1) % size_map_y]);
//	creature->see[3].push_back(&map[(creature->map_cord.first - creature->see[3].size() - 1 + size_map_x) % size_map_x][creature->map_cord.second]);
//}
//
//void Action_go(Creature* creature)
//{
//	//if (creature->get_TYPE_CREATURE() == TYPE_CREATURE::HERBIVORE) {
//	//	creature->energy -= use_energy(20);
//	//}
//	//else {
//	//creature->energy -= use_energy(40);
//	//}
//
//	std::pair<int, int> next = creature->map_cord;
//	switch (creature->dir)
//	{
//	case DIRECTION::UP:
//		next.second = (next.second - 1 + size_map_y) % size_map_y;
//		break;
//	case DIRECTION::RIGHT:
//		next.first = (next.first + 1) % size_map_x;
//		break;
//	case DIRECTION::DOWN:
//		next.second = (next.second + 1) % size_map_y;
//		break;
//	case DIRECTION::LEFT:
//		next.first = (next.first - 1 + size_map_x) % size_map_x;
//		break;
//	}
//
//	if (map[next.first][next.second].get_TYPE_CREATURE() == TYPE_CREATURE::Void) {
//		creature->see[turn(creature->dir, DIRECTION::to_LEFT)].clear();
//		creature->see[turn(creature->dir, DIRECTION::to_RIGHT)].clear();
//		if (creature->see[turn(creature->dir, DIRECTION::to_FORWARD)].size() != 0) {
//			creature->see[turn(creature->dir, DIRECTION::to_FORWARD)].erase(creature->see[turn(creature->dir, DIRECTION::to_FORWARD)].begin());
//		}
//		creature->see[turn(creature->dir, DIRECTION::to_BACK)].insert(creature->see[turn(creature->dir, DIRECTION::to_BACK)].begin(), creature->get_under_me());
//
//		creature->see[DIRECTION::UNDER][0] = &map[next.first][next.second];
//
//		map[next.first][next.second].swap_creapure(&map[creature->map_cord.first][creature->map_cord.second]);
//		creature->map_cord = next;
//	}
//}
//
//void Action_turn_right(Creature* creature) {
//	//creature->energy -= use_energy(20);
//
//	creature->dir = turn(creature->dir, DIRECTION::to_RIGHT);
//}
//
//void Action_turn_left(Creature* creature) {
//	//creature->energy -= use_energy(20);
//
//	creature->dir = turn(creature->dir, DIRECTION::to_LEFT);
//}
//
//void Action_eat_(Creature* creature) {
//	//creature->energy -= use_energy(70);
//
//	switch (creature->get_TYPE_CREATURE())
//	{
//	case TYPE_CREATURE::PLANT:
//		//creature->energy += max(limit_energy - (creature->get_under_me()->free_energy += 30), 0);
//	{
//		int tmp = max(400 - creature->get_under_me()->free_energy, 0);
//		//int tmp = max(limit_energy - creature->get_under_me()->free_energy * 7, 0);
//		creature->energy += tmp;
//		//creature->get_under_me()->free_energy += tmp / 4;
//		break;
//	}
//	case TYPE_CREATURE::HERBIVORE:
//	{
		//if (creature->see[creature->dir].size() == 0) {
		//	Action_look(creature);
		//}

//if (creature->see[creature->dir][0]->get_TYPE_CREATURE() != TYPE_CREATURE::Void) {
		//	int out = creature->see[creature->dir][0]->set_creature();
		//	creature->see[creature->dir][0]->free_energy += out / 3;
		//	creature->energy += out / 2;
		//}	//Action_go(creature);
		////}
		////else {
		////	creature->energy += use_energy(90);
		////}
		//break;
//	}
//	case TYPE_CREATURE::SCAVENGER:
//	{
//		//creature->energy += max(creature->get_under_me()->free_energy, 0);
//		//creature->get_under_me()->free_energy = 0;
//
//		int tmp = min(creature->get_under_me()->free_energy, 400);
//		//int tmp = creature->get_under_me()->free_energy / 7;
//		creature->energy += tmp;
//		creature->get_under_me()->free_energy -= tmp;
//		break;
//	}
//	}
//}


/*

class Condition
	{
	public:
		Condition(int power, int true_iter, int false_iter, Creature* creature, DIRECTION to_dir, TYPE_CREATURE type_creature, int found_level_under, void (*Action)(Creature* creature) = nullptr);

		bool use(int power_step);

		void set_creature(Creature* creature);
	private:
		Creature* creature;
		DIRECTION to_dir;
		TYPE_CREATURE found_type_creature;
		int found_level_under;

		//bool (*Action)(Creature* creature, DIRECTION dir, Cell* cell);
		//bool (*Cond)(Creature* creature, DIRECTION dir, TYPE_CREATURE type_creature);

		int power;      // количество повторений этого действия за дин ход
		int power_step;
		int true_iter;
		int false_iter;

		void (*Action)(Creature* creature);

		bool Cond();
	};
*/

