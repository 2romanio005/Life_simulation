#pragma once
#include "MainConnection.h"
#include "Actions.h"




//int use_energy(int energy) {
//	return energy;
//}



std::string string_by_dir_for_condition(Direction dir)
{
	switch (dir)
	{
	case Direction::to_FORWARD:
		return "Спереди";
		break;
	case Direction::to_RIGHT:
		return "Справа";
		break;
	case Direction::to_LEFT:
		return "Слева";
		break;
	case Direction::to_BACK:
		return "Сзади";
		break;
	case Direction::UP:
		return "Верх";
		break;
	case Direction::RIGHT:
		return "Право";
		break;
	case Direction::DOWN:
		return "Низ";
		break;
	case Direction::LEFT:
		return "Лево";
		break;
	case Direction::UNDER:
		return "Снизу";
		break;
	}
}

std::string string_by_dir_for_turn(Direction dir)
{
	switch (dir)
	{
	case Direction::to_FORWARD:
		return "Вперёд";
		break;
	case Direction::to_RIGHT:
		return "Направо";
		break;
	case Direction::to_LEFT:
		return "Налево";
		break;
	case Direction::to_BACK:
		return "Назад";
		break;
	case Direction::UP:
		return "Верх";
		break;
	case Direction::RIGHT:
		return "Право";
		break;
	case Direction::DOWN:
		return "Низ";
		break;
	case Direction::LEFT:
		return "Лево";
		break;
	case Direction::UNDER:
		return "Снизу";
		break;
	}
}

std::string string_by_type_creature(Type_Creature type_creature)
{
	switch (type_creature)
	{
	case Plant:
		return "Растение";
		break;
	case Herbivore:
		return "Хищник";
		break;
	case Scavenger:
		return "Падальщик";
		break;
	case Void:
		return "Никого";
		break;
	}
}



Action* get_rand_Action(Creature* creature, unsigned int max_iter) {
	switch (rand() % 5)
	{
	case 0:
		return new Action_go(creature);
		break;
	case 1:
		return new Action_eat(creature);
		break;
	case 2:
		return new Action_turn(creature, Direction(rand() % 3 - 3));
		break;
	case 3:
		return new Action_condition_by_Type_Creature(creature, Direction(rand() % 4 - 4), rand() % max_iter, rand() % max_iter, Type_Creature(rand() % 4));
		break;
	case 4:
	{
		/*bool (*cond)(int one, int two) = [](int one, int two)->bool { return one >= two; };
		if (rand() % 2) {
			cond = [](int one, int two)->bool { return one >= two; };
		}*/
		int tmp = (rand() % 5);
		return new Action_condition_by_Cell(creature, Direction(tmp == 4 ? 4 : tmp - 4), rand() % max_iter, rand() % max_iter, rand() % limit_energy);
		break;
	}
	//case 5:
	//	return new Action_change_iter(creature, rand() % max_iter);
	//	break;
	}
	
}



Action::Action(Creature* creature)
{
	this->creature = creature;
}

bool Action::mutation()
{
	return false;
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
		out->second = max(sample[i].size(), out->second);
		(*out).first += sample[i] + '\n';
	}

	delete[] sample;
	return out;
}



Action_go::Action_go(Creature* creature) : Action(creature)
{
}

bool Action_go::use()
{
	std::pair<int, int> next = near_cell_cord(this->creature->map_cord, this->creature->dir);

	if (map[next.first][next.second].get_Type_Creature() == Type_Creature::Void) {
		map[next.first][next.second].swap_Creapure(&map[creature->map_cord.first][creature->map_cord.second]);
		creature->map_cord = next;
	}

	this->creature->next_iter();
	return true;
}

Action* Action_go::copy()
{
	return new Action_go(this->creature);
}

std::string* Action_go::draw_myself()
{
	return new std::string[5]
		{
			"Идти",
			"",
			"",
			"",
			""
		}
	;
}

void Action_go::write_myself(std::string* out)
{
	*out += 
		std::to_string(this->get_Type_Action())
		+ ";0;0;0;0;";
}

Type_Action Action_go::get_Type_Action()
{
	return Type_Action::GO;
}


Action_eat::Action_eat( Creature* creature) : Action(creature)
{
}

bool Action_eat::use()
{
	switch (creature->get_Type_Creature())
	{
	case Type_Creature::Plant:
	{
		//creature->energy += max(limit_energy - (creature->get_under_me()->free_energy += 30), 0);
		//int tmp = max(400 - this->creature->get_under_me()->get_free_energy(), 0);
		//int tmp = (limit_energy / 15 - creature->get_under_me()->get_free_energy());
		//int tmp = (limit_energy - creature->get_under_me()->get_free_energy()) / 7;
		//int tmp = (limit_energy - creature->get_under_me()->get_free_energy() * 15);
		int tmp = limit_energy - creature->get_under_me()->get_free_energy() * (100 - PosSliderGreenEat);
		if (tmp < 0) tmp = 0;
		this->creature->energy += tmp;
		//creature->get_under_me()->change_free_energy(1);
		break;
	}
	case Type_Creature::Herbivore:
	{
		Cell* next_cell = get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, this->creature->dir));

		if (next_cell->get_Type_Creature() != Type_Creature::Void) {
			int out = next_cell->get_Creature_energy();
			next_cell->set_Creature();

			next_cell->change_free_energy((out * PosSliderRedLeave) / 100);
			this->creature->energy +=  (out * PosSliderRedEat) / 100;
		}
		break;
	}
	case Type_Creature::Scavenger:
	{
		//creature->energy += max(creature->get_under_me()->free_energy, 0);
		//creature->get_under_me()->free_energy = 0;

		//int tmp = min(creature->get_under_me()->get_free_energy(), 400);
		//int tmp = creature->get_under_me()->get_free_energy() / 6;
		int tmp = creature->get_under_me()->get_free_energy();
		if (tmp > 50) {
			tmp = (tmp * PosSliderBlueEat) / 100;
		}
		this->creature->energy += tmp;
		this->creature->get_under_me()->change_free_energy(-tmp);
		break;
	}
	}

	this->creature->next_iter();
	return true;
}

Action* Action_eat::copy()
{
	return new Action_eat(this->creature);
}

std::string* Action_eat::draw_myself()
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

void Action_eat::write_myself(std::string* out)
{
	*out += 
		std::to_string(this->get_Type_Action())
		+ ";0;0;0;0;";
}

Type_Action Action_eat::get_Type_Action()
{
	return Type_Action::EAT;
}


Action_turn::Action_turn(Creature* creature, Direction to_dir) : Action(creature)
{
	this->to_dir = to_dir;
}

bool Action_turn::use()
{
	this->creature->dir = turn(this->creature->dir, this->to_dir);

	this->creature->next_iter();
	return false;
}

bool Action_turn::mutation()
{
	this->to_dir = Direction(rand() % 3 - 3);
	return true;
}

Action* Action_turn::copy()
{
	return new Action_turn(this->creature, this->to_dir);
}

std::string* Action_turn::draw_myself()
{
	return new std::string[5]
		{
			"Поворот",
			string_by_dir_for_turn(this->to_dir),
			"",
			"",
			""
		};
}

void Action_turn::write_myself(std::string* out)
{
	*out += 
		std::to_string(this->get_Type_Action())
		+ ';' + std::to_string(this->to_dir)
		+ ";0;0;0;";
}

Type_Action Action_turn::get_Type_Action()
{
	return Type_Action::TURN;
}


Action_condition_by_Type_Creature::Action_condition_by_Type_Creature(Creature* creature, Direction to_dir, unsigned int true_iter, unsigned int false_iter, Type_Creature type_creature) : Action(creature)
{
	this->to_dir = to_dir;

	this->true_iter = true_iter;
	this->false_iter = false_iter;

	this->type_creature = type_creature;
}

bool Action_condition_by_Type_Creature::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, turn(this->creature->dir, this->to_dir)))->get_Type_Creature() == this->type_creature) {
		this->creature->iter = this->true_iter;
	}
	else {
		this->creature->iter = this->false_iter;
	}

	return false;
}

bool Action_condition_by_Type_Creature::mutation()
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
		this->to_dir = Direction(rand() % 4 - 4);
		break;
	case 3:
		this->type_creature = Type_Creature(rand() % 4);
		break;
	}

	return true;
}

Action* Action_condition_by_Type_Creature::copy()
{
	return new Action_condition_by_Type_Creature(this->creature, this->to_dir, this->true_iter, this->false_iter,this->type_creature);
}

std::string* Action_condition_by_Type_Creature::draw_myself()
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

void Action_condition_by_Type_Creature::write_myself(std::string* out)
{
	*out += 
		std::to_string(this->get_Type_Action())
		+ ';' + std::to_string(this->to_dir)
		+ ';' + std::to_string(this->type_creature)
		+ ';' + std::to_string(this->true_iter)
		+ ';' + std::to_string(this->false_iter)
		+ ';';
}

Type_Action Action_condition_by_Type_Creature::get_Type_Action()
{
	return Type_Action::CONDITION_BY_TYPE_CREATURE;
}


Action_condition_by_Cell::Action_condition_by_Cell(Creature* creature, Direction to_dir, unsigned int true_iter, unsigned int false_iter, int limit/*, bool (*cond)(int one, int two)*/) : Action(creature)
{
	this->to_dir = to_dir;

	this->true_iter = true_iter;
	this->false_iter = false_iter;

	this->limit = limit;
	//this->cond = cond;
}

bool Action_condition_by_Cell::use()
{
	if (get_Cell_by_map_cord(near_cell_cord(this->creature->map_cord, this->to_dir == Direction::UNDER ? Direction::UNDER : turn(this->creature->dir, this->to_dir)))->get_free_energy() >= this->limit) {
		this->creature->iter = this->true_iter;
	}
	else {
		this->creature->iter = this->false_iter;
	}

	return false;
}

bool Action_condition_by_Cell::mutation()
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
		this->to_dir = Direction(rand() % 4 - 4);
		break;
	case 3:
		this->limit = Type_Creature(rand() % limit_energy);
		break;
	}
	return true;
}

Action* Action_condition_by_Cell::copy()
{
	return new Action_condition_by_Cell(this->creature, this->to_dir, this->true_iter, this->false_iter, this->limit);
}

std::string* Action_condition_by_Cell::draw_myself()
{
	return new std::string[5]
		{
			"Условие",
			string_by_dir_for_condition(this->to_dir),
			std::to_string(this->limit),
			std::to_string(this->true_iter),
			std::to_string(this->false_iter)
		};
}

void Action_condition_by_Cell::write_myself(std::string* out)
{
	*out += 
		std::to_string(this->get_Type_Action())
		+ ';' + std::to_string(this->to_dir)
		+ ';' + std::to_string(this->limit)
		+ ';' + std::to_string(this->true_iter)
		+ ';' + std::to_string(this->false_iter)
		+ ';';
}

Type_Action Action_condition_by_Cell::get_Type_Action()
{
	return Type_Action::CONDITION_BY_CELL;
}


Action_change_iter::Action_change_iter(Creature* creature, unsigned int iter) : Action(creature)
{
	this->iter = iter;
}

bool Action_change_iter::use()
{
	this->creature->iter = this->iter;

	return false;
}

bool Action_change_iter::mutation()
{
	this->iter = rand() % this->creature->brain.size();
	return true;
}

Action* Action_change_iter::copy()
{
	return new Action_change_iter(this->creature, this->iter);
}

std::string* Action_change_iter::draw_myself()
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

void Action_change_iter::write_myself(std::string* out)
{
	*out += 
		std::to_string(this->get_Type_Action())
		+ ";0;0"
		+ ';' + std::to_string(this->iter)
		+ ';' + std::to_string(this->iter)
		+ ';';
}

Type_Action Action_change_iter::get_Type_Action()
{
	return Type_Action::CHANGE_ITER;
}














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
//	//if (creature->get_Type_Creature() == Type_Creature::Herbivore) {
//	//	creature->energy -= use_energy(20);
//	//}
//	//else {
//	//creature->energy -= use_energy(40);
//	//}
//
//	std::pair<int, int> next = creature->map_cord;
//	switch (creature->dir)
//	{
//	case Direction::UP:
//		next.second = (next.second - 1 + size_map_y) % size_map_y;
//		break;
//	case Direction::RIGHT:
//		next.first = (next.first + 1) % size_map_x;
//		break;
//	case Direction::DOWN:
//		next.second = (next.second + 1) % size_map_y;
//		break;
//	case Direction::LEFT:
//		next.first = (next.first - 1 + size_map_x) % size_map_x;
//		break;
//	}
//
//	if (map[next.first][next.second].get_Type_Creature() == Type_Creature::Void) {
//		creature->see[turn(creature->dir, Direction::to_LEFT)].clear();
//		creature->see[turn(creature->dir, Direction::to_RIGHT)].clear();
//		if (creature->see[turn(creature->dir, Direction::to_FORWARD)].size() != 0) {
//			creature->see[turn(creature->dir, Direction::to_FORWARD)].erase(creature->see[turn(creature->dir, Direction::to_FORWARD)].begin());
//		}
//		creature->see[turn(creature->dir, Direction::to_BACK)].insert(creature->see[turn(creature->dir, Direction::to_BACK)].begin(), creature->get_under_me());
//
//		creature->see[Direction::UNDER][0] = &map[next.first][next.second];
//
//		map[next.first][next.second].swap_creapure(&map[creature->map_cord.first][creature->map_cord.second]);
//		creature->map_cord = next;
//	}
//}
//
//void Action_turn_right(Creature* creature) {
//	//creature->energy -= use_energy(20);
//
//	creature->dir = turn(creature->dir, Direction::to_RIGHT);
//}
//
//void Action_turn_left(Creature* creature) {
//	//creature->energy -= use_energy(20);
//
//	creature->dir = turn(creature->dir, Direction::to_LEFT);
//}
//
//void Action_eat_(Creature* creature) {
//	//creature->energy -= use_energy(70);
//
//	switch (creature->get_Type_Creature())
//	{
//	case Type_Creature::Plant:
//		//creature->energy += max(limit_energy - (creature->get_under_me()->free_energy += 30), 0);
//	{
//		int tmp = max(400 - creature->get_under_me()->free_energy, 0);
//		//int tmp = max(limit_energy - creature->get_under_me()->free_energy * 7, 0);
//		creature->energy += tmp;
//		//creature->get_under_me()->free_energy += tmp / 4;
//		break;
//	}
//	case Type_Creature::Herbivore:
//	{
//		if (creature->see[creature->dir].size() == 0) {
//			Action_look(creature);
//		}
//
//		if (creature->see[creature->dir][0]->get_Type_Creature() != Type_Creature::Void) {
//			int out = creature->see[creature->dir][0]->set_creature();
//			creature->see[creature->dir][0]->free_energy += out / 3;
//			creature->energy += out / 2;
//		}	//Action_go(creature);
//		//}
//		//else {
//		//	creature->energy += use_energy(90);
//		//}
//		break;
//	}
//	case Type_Creature::Scavenger:
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
		Condition(int power, int true_iter, int false_iter, Creature* creature, Direction to_dir, Type_Creature type_creature, int found_level_under, void (*Action)(Creature* creature) = nullptr);

		bool use(int power_step);

		void set_creature(Creature* creature);
	private:
		Creature* creature;
		Direction to_dir;
		Type_Creature found_type_creature;
		int found_level_under;

		//bool (*Action)(Creature* creature, Direction dir, Cell* cell);
		//bool (*Cond)(Creature* creature, Direction dir, Type_Creature type_creature);

		int power;      // количество повторений этого действия за дин ход
		int power_step;
		int true_iter;
		int false_iter;

		void (*Action)(Creature* creature);

		bool Cond();
	};
*/


