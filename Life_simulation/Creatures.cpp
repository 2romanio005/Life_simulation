#include "Creatures.h"
#include "MainConnection.h"


/*

Creature::Condition::Condition(int power, int true_iter, int false_iter, Creature* creature, Direction to_dir, Type_Creature found_type_creature, int found_level_under, void (*Action)(Creature* creature)) {
	this->power = power;
	this->power_step = 1;
	this->true_iter = true_iter;
	this->false_iter = false_iter;
	this->creature = creature;
	this->to_dir = to_dir;
	this->found_type_creature = found_type_creature;
	this->found_level_under = found_level_under;

	this->Action = Action;
}



bool Creature::Condition::use(int power_step) {
	if (this->creature->get_Type_Creature() == Type_Creature::Herbivore) {
 		int a = 0;
	}

	if (true_iter == -1) {
		if (power_step == this->power_step) {
			this->power_step++;
			this->Action(this->creature);
			if (power_step == this->power) {
				this->power_step = 1;
				creature->iter = (creature->iter + 1) % creature->brain.size();
			}
		}
		return false;
	}

	if (this->Cond()) {       // пофиксить когда после условия пришло к действию и не доделает его до конца тк уже потратил степы  !!!!!!!!!!!
		creature->iter = true_iter;
	}
	else {
		creature->iter = false_iter;
	}
	return true;
}

void Creature::Condition::set_creature(Creature* creature)
{
	this->creature = creature;
}

bool Creature::Condition::Cond()
{
	if (this->to_dir == Direction::UNDER) {
		switch (this->creature->get_Type_Creature())
		{
		case Type_Creature::Plant:
			return this->creature->see[4][0]->free_energy <= this->found_level_under;
			break;
		case Type_Creature::Herbivore:
		case Type_Creature::Scavenger:
			return this->creature->see[4][0]->free_energy >= this->found_level_under;
			break;
		}
	}

	for (Cell* check : this->creature->see[turn(this->creature->dir, this->to_dir)]) {
		if (check->get_Type_Creature() == this->found_type_creature) { return true; }
	}
	return false;
}

*/


Direction turn(Direction strt, Direction step)
{
	return Direction((strt + step + 4) % 4);
}

std::pair<int, int> near_cell_cord(std::pair<int, int> now_map_cord, Direction to_dir)
{
	switch (to_dir)
	{
	case Direction::UP:
		now_map_cord.second = (now_map_cord.second - 1 + size_map_y) % size_map_y;
		break;
	case Direction::RIGHT:
		now_map_cord.first = (now_map_cord.first + 1) % size_map_x;
		break;
	case Direction::DOWN:
		now_map_cord.second = (now_map_cord.second + 1) % size_map_y;
		break;
	case Direction::LEFT:
		now_map_cord.first = (now_map_cord.first - 1 + size_map_x) % size_map_x;
		break;
	case Direction::UNDER:// так хорошо
		break;
	}
	return now_map_cord;
}

Creature* parse_str_to_Creature(const std::pair<int, int>& map_cord, std::string str)
{
	int iter = 0;

	Type_Creature type_creature = Type_Creature(parse_str_to_int_one_step(str, &iter));
	if (type_creature == Type_Creature::Void) return nullptr;

	Direction dir = Direction(parse_str_to_int_one_step(str, &iter));
	int age = parse_str_to_int_one_step(str, &iter), energy = parse_str_to_int_one_step(str, &iter), lim_energy = parse_str_to_int_one_step(str, &iter), br_iter = parse_str_to_int_one_step(str, &iter), br_size = parse_str_to_int_one_step(str, &iter);

	std::vector<Action*> br;
	br.reserve(br_size);
	for (int i = 0; i < br_size; i++)
	{
		int arr[5]{};
		for (int j = 0; j < 5; j++)
		{
			arr[j] = parse_str_to_int_one_step(str, &iter);
		}

		switch (Type_Action(arr[0]))
		{
		case GO:
			br.push_back(new Action_go(nullptr));
			break;
		case EAT:
			br.push_back(new Action_eat(nullptr));
			break;
		case TURN:
			br.push_back(new Action_turn(nullptr, Direction(arr[1])));
			break;
		case CONDITION_BY_TYPE_CREATURE:
			br.push_back(new Action_condition_by_Type_Creature(nullptr, Direction(arr[1]), arr[3], arr[4], Type_Creature(arr[2])));
			break;
		case CONDITION_BY_CELL:
			br.push_back(new Action_condition_by_Cell(nullptr, Direction(arr[1]), arr[3], arr[4], arr[2]));
			break;
		case CHANGE_ITER:
			br.push_back(new Action_change_iter(nullptr, arr[3]));
			break;
		}
	}
	
	switch (type_creature)
	{
	case Plant:
		return new Creature_Plant(map_cord, energy, lim_energy, dir, age, &br, br_iter);
		break;
	case Herbivore:
		return new Creature_Herbivore(map_cord, energy, lim_energy, dir, age, &br, br_iter);
		break;
	case Scavenger:
		return new Creature_Scavenger(map_cord, energy, lim_energy, dir, age, &br, br_iter);
		break;
	}
}

std::vector<Action*>* copy_brain(const std::vector<Action*>& sample_brain) {
	std::vector<Action*>* br = new std::vector<Action*>(sample_brain.size(), nullptr);

	for (unsigned int i = 0; i < sample_brain.size(); i++)
	{
		(*br)[i] = sample_brain[i]->copy();
	}
	return br;
}



Creature::Creature(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age, std::vector<Action*>* brain, unsigned int iter)
{
	this->age = age;
	this->energy = energy;
	this->lim_energy = lim_energy;
	this->iter = iter;
	this->dir = dir;
	this->map_cord = map_cord;

	this->flag_step = true;

	if (brain == nullptr) {
		this->create_Action((rand() % 4) + 1, &this->brain);
	}
	else {
		for (auto& act : *brain)
		{
			act->set_Creature(this);    // пометил как свой
		}
		this->brain = *brain;    // скопировал мозг и хранит как свой
	}
}

Creature::~Creature()
{
	for (auto& act : this->brain) {
		delete act;
		act = nullptr;
	}
	this->brain.clear();
}

void Creature::step() {
	if (this->flag_step) {
		this->flag_step = false;
		for (int i = 0; i < limit_power_step && !this->brain[this->iter]->use(); ++i) {};   // цикл для прокрутки условий 

		int tmp = 0;
		switch (this->get_Type_Creature())
		{
		case Type_Creature::Plant:
			tmp = Creature_Plant::get_type_count();
			break;
		case Type_Creature::Herbivore:
			tmp = Creature_Herbivore::get_type_count();
			break;
		case Type_Creature::Scavenger:
			tmp = Creature_Scavenger::get_type_count();
			break;
		}
		//this->energy -= 100.0 * (CountPlant + CountScavenger + CountHerbivore) / (size_map_x * size_map_y);
		//this->energy -= int(float(limit_energy / 8) * (tmp * 2) / (size_map_x * size_map_y) + this->brain.size());
		this->energy -= (limit_energy * PosSliderAllLose * tmp) / (size_map_x * size_map_y * 100);
		//this->energy -= int(float(limit_energy / 20) * (tmp * 4) / (size_map_x * size_map_y) + this->brain.size());

		if (this->energy < 0) {
			this->get_under_me()->set_Creature();
		}
	}
}

void Creature::one_step_finish()
{
	this->flag_step = true;


	if (this->energy > this->lim_energy) {
		
		Cell* near_place;
		if (FlagRandDivision) {
			near_place = &map[rand() % size_map_x][rand() % size_map_y];
		}
		else {
			near_place = get_Cell_by_map_cord(near_cell_cord(this->map_cord, turn(this->dir, Direction::to_BACK)));
		}
		if (near_place->get_Type_Creature() == Type_Creature::Void) {
			this->energy /= 3;

			std::vector<Action*>* br = copy_brain(this->brain);

			int new_lim_energy = this->lim_energy;

			if (rand() % 100 < mut_chence) {    // мутация
				//this->create_Action(rand() % (this->brain.size() + 1), br);
				this->create_Action(rand() % max(this->brain.size() + 1, 100), br);
			}
			if (rand() % 20 == 0) {
				new_lim_energy = (rand() % limit_energy) + 5;
			}

			Creature* cr = nullptr;
			switch (((rand() % 100) < mut_type_chence) ? (rand() % 3) : this->get_Type_Creature())
			{
			case Type_Creature::Plant:
				cr = new Creature_Plant(near_place->get_map_cord(), this->energy, new_lim_energy, Direction(rand() % 4), 0, br);
				break;
			case Type_Creature::Herbivore:
				cr = new Creature_Herbivore(near_place->get_map_cord(), this->energy, new_lim_energy, Direction(rand() % 4), 0, br);
				break;
			case Type_Creature::Scavenger:
				cr = new Creature_Scavenger(near_place->get_map_cord(), this->energy, new_lim_energy, Direction(rand() % 4), 0, br);
				break;
			default:
				throw;
				break;
			}
			near_place->set_Creature(cr);
			delete br;
		}


		/*Direction rand_dir = Direction((rand() % 4) - 4);     // вариант с просмотром вариантов со всех сторон
		for (int i = 0; i < 4; i++)
		{
			Direction test_dir = turn(Direction(i), rand_dir);

			if (this->see[test_dir].size() == 0) {
				Action_look(this);
			}

			if (this->see[test_dir][0]->get_Type_Creature() == Type_Creature::Void) {
				this->energy /= 2;

				Cell* free_place = free_place = this->see[test_dir][0];
				std::vector<Creature_Scavenger::Condition> br = this->brain;
				int new_lim_energy = this->lim_energy;

				if (rand() % 100 < mut_chence) {    // мутация
					this->create_Action(rand() % (this->brain.size() + 1), &br);
					if (rand() % 2) {
						new_lim_energy = rand() % limit_energy;
					}
				}

				Creature* cr = nullptr;
				switch (((rand() % 100) < mut_type_chence) ? (rand() % 3) : this->get_Type_Creature())
				{
				case Type_Creature::Plant:
					cr = new Creature_Plant(free_place->get_map_cord(), this->energy, new_lim_energy, &br);
					break;
				case Type_Creature::Herbivore:
					cr = new Creature_Herbivore(free_place->get_map_cord(), this->energy, new_lim_energy, &br);
					break;
				case Type_Creature::Scavenger:
					cr = new Creature_Scavenger(free_place->get_map_cord(), this->energy, new_lim_energy, &br);
					break;
				default:
					throw;
					break;
				}
				free_place->set_creature(cr);

				break;
			}
		}*/
	
	}


	if (++this->age > limit_age) {
		//this->get_under_me()->change_free_energy(10);
		this->get_under_me()->change_free_energy(max(this->energy >> 5, 10));
		this->get_under_me()->set_Creature();
	}
}



void Creature::build_brain(HWND hWnd)
{
	for (int i = this->brain.size(); i < StaticPeepBrain.size(); i++)
	{
		ShowWindow(StaticPeepBrain[i].first, SW_HIDE);
		DestroyWindow(StaticPeepBrain[i].first);
	}
	for (int i = StaticPeepBrain.size(); i < this->brain.size(); i++)
	{
		StaticPeepBrain.push_back({ CreateWindowA("STATIC", "", WS_CHILD | ES_CENTER, 0, 0, 0, 0, hWnd, NULL, NULL, NULL), 0});
	}
	StaticPeepBrain.resize(this->brain.size());


	for (int i = 0; i < this->brain.size(); i++)
	{
		std::pair<std::string, int>* act = this->brain[i]->build_draw();
		SetWindowTextA(StaticPeepBrain[i].first, LPCSTR((std::to_string(i) + '\n' + act->first).c_str()));
		StaticPeepBrain[i].second = act->second * 10;
		SetWindowPos(StaticPeepBrain[i].first, nullptr, 0, 0, StaticPeepBrain[i].second, 96, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		delete act; /// !!!!!!!!!!!!!!!!!!!!!
	}

}

void Creature::draw_brain()
{
	for (int i = 0; i < StaticPeepBrain.size(); i++)
	{
		ShowWindow(StaticPeepBrain[i].first, SW_HIDE);
		//SetWindowPos(StaticPeepBrain[i].first, nullptr, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOREDRAW);
	}


	//unsigned int i = 0;
	//for (; i < PosSliderPeepBrain; i++)
	//{
	//	ShowWindow(StaticPeepBrain[i].first, SW_HIDE);
	//}
	int width = margin_x + 43;
	for (unsigned int i = PosSliderPeepBrain; i < this->brain.size(); i++)
	{
		if ((width += StaticPeepBrain[i].second) > margin_x + size_map_x * size_cell) {
			break;
		}

		SetWindowPos(StaticPeepBrain[i].first, nullptr, width - StaticPeepBrain[i].second, margin_y * 2 + size_map_y * size_cell + 20, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		//ShowWindow(StaticPeepBrain[i].first, SW_SHOW);
	}
	//for (; i < this->brain.size(); i++)
	//{
	//	ShowWindow(StaticPeepBrain[i].first, SW_HIDE);
	//}
}

std::string Creature::write_myself()
{
	std::string out = 
		std::to_string(this->get_Type_Creature()) + ';'
		+ std::to_string(this->dir) + ';'
		+ std::to_string(this->age) + ';' 
		+ std::to_string(this->energy) + ';'
		+ std::to_string(this->lim_energy) + ';'
		+ std::to_string(this->iter) + ';'
		+ std::to_string(this->brain.size()) + ';';

	for (auto& act : this->brain) {
		act->write_myself(&out);
	}

	return out + '\n';
}



Direction Creature::get_dir()
{
	return this->dir;
}

int Creature::get_energy()
{
	return this->energy;
}

int Creature::get_lim_energy()
{
	return this->lim_energy;
}

int Creature::get_age()
{
	return this->age;
}

int Creature::get_iter()
{
	return this->iter;
}

int Creature::get_brain_size()
{
	return this->brain.size();
}


void Creature::create_Action(unsigned int mut_iter, std::vector<Action*>* change_brain)   // !!!!!!!!!!!!!!! название
{
	if (change_brain->size() > mut_iter) {
		if (rand() % 2 || !(*change_brain)[mut_iter]->mutation()) {   // изменить весь ген / часть его
			delete (*change_brain)[mut_iter];
			(*change_brain)[mut_iter] = get_rand_Action(this, change_brain->size());
		}
		return;
	}
	
	while (mut_iter >= change_brain->size()) {
		change_brain->push_back(get_rand_Action(this, mut_iter));

	}
	for (auto& act : this->brain)
	{
		if (rand() % 2) {
			act->mutation();
		}
	}
}

Cell* Creature::get_under_me()
{
	return get_Cell_by_map_cord(this->map_cord);
}

void Creature::next_iter()
{
	this->iter = (this->iter + 1) % this->brain.size();
}





Creature_Plant::Creature_Plant(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age, std::vector<Action*>* brain, unsigned int iter) : Creature(map_cord, energy, lim_energy, dir, age, brain, iter) {
	this->CountPlant++;
}
int Creature_Plant::CountPlant = 0;

Creature_Plant::~Creature_Plant() {
	this->CountPlant--;
}

Creature* Creature_Plant::copy(std::pair<int, int> map_cord) {
	std::vector<Action*>* br = copy_brain(this->brain);
	return new Creature_Plant(map_cord, this->energy, this->lim_energy, this->dir, this->age, br, this->iter);
	delete br;
}

void Creature_Plant::draw_myself(HDC hdc, std::pair<int, int> cord)
{
	int r = int(size_cell * 0.4);
	cord.first += size_half_cell; cord.second += size_half_cell;
	SelectObject(hdc, H_Green);
	RoundRect(hdc, cord.first - r, cord.second - r, cord.first + r, cord.second + r, r * 2, r * 2);
}

int Creature_Plant::get_type_count()
{
	return CountPlant;
}

Type_Creature Creature_Plant::get_Type_Creature() {
	return Plant;
}



Creature_Herbivore::Creature_Herbivore(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age, std::vector<Action*>* brain, unsigned int iter) : Creature(map_cord, energy, lim_energy, dir, age, brain, iter) {
	this->CountHarbivore++;
}
int Creature_Herbivore::CountHarbivore = 0;

Creature_Herbivore::~Creature_Herbivore() {
	this->CountHarbivore--;
}

Creature* Creature_Herbivore::copy(std::pair<int, int> map_cord) {
	std::vector<Action*>* br = copy_brain(this->brain);
	return new Creature_Herbivore(map_cord, this->energy, this->lim_energy, this->dir, this->age, copy_brain(this->brain), this->iter);
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
	return CountHarbivore;
}

Type_Creature Creature_Herbivore::get_Type_Creature() {
	return Herbivore;
}



Creature_Scavenger::Creature_Scavenger(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age, std::vector<Action*>* brain, unsigned int iter) : Creature(map_cord, energy, lim_energy, dir, age, brain, iter) {
	this->CountScavenger++;
}
int Creature_Scavenger::CountScavenger = 0;

Creature_Scavenger::~Creature_Scavenger() {
	this->CountScavenger--;
}

Creature* Creature_Scavenger::copy(std::pair<int, int> map_cord) {
	std::vector<Action*>* br = copy_brain(this->brain);
	return new Creature_Scavenger(map_cord, this->energy, this->lim_energy, this->dir, this->age, copy_brain(this->brain), this->iter);
	delete br;
}

void Creature_Scavenger::draw_myself(HDC hdc, std::pair<int, int> cord)
{
	int r = int(size_cell * 0.4);
	cord.first += size_half_cell; cord.second += size_half_cell;
	SelectObject(hdc, H_Blue);
	RoundRect(hdc, cord.first - r, cord.second - r, cord.first + r, cord.second + r, r * 2, r * 2);
}

int Creature_Scavenger::get_type_count()
{
	return CountScavenger;
}

Type_Creature Creature_Scavenger::get_Type_Creature()
{
	return Scavenger;
}







