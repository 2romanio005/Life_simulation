п»ї#pragma once
#include "Creatures.h"
#include "Creature_Plant.h"
#include "Creature_Herbivore.h"
#include "Creature_Scavenger.h"

/*

Creature::Condition::Condition(int power, int true_iter, int false_iter, Creature* creature, DIRECTION to_dir, TYPE_CREATURE found_type_creature, int found_level_under, void (*Action)(Creature* creature)) {
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
	if (this->creature->get_TYPE_CREATURE() == TYPE_CREATURE::Herbivore) {
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

	if (this->Cond()) {       // РїРѕС„РёРєСЃРёС‚СЊ РєРѕРіРґР° РїРѕСЃР»Рµ СѓСЃР»РѕРІРёСЏ РїСЂРёС€Р»Рѕ Рє РґРµР№СЃС‚РІРёСЋ Рё РЅРµ РґРѕРґРµР»Р°РµС‚ РµРіРѕ РґРѕ РєРѕРЅС†Р° С‚Рє СѓР¶Рµ РїРѕС‚СЂР°С‚РёР» СЃС‚РµРїС‹  !!!!!!!!!!!
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
	if (this->to_dir == DIRECTION::UNDER) {
		switch (this->creature->get_TYPE_CREATURE())
		{
		case TYPE_CREATURE::Plant:
			return this->creature->see[4][0]->free_energy <= this->found_level_under;
			break;
		case TYPE_CREATURE::Herbivore:
		case TYPE_CREATURE::Scavenger:
			return this->creature->see[4][0]->free_energy >= this->found_level_under;
			break;
		}
	}

	for (Cell* check : this->creature->see[turn(this->creature->dir, this->to_dir)]) {
		if (check->get_TYPE_CREATURE() == this->found_type_creature) { return true; }
	}
	return false;
}

*/


std::pair<int, int> near_cell_cord(std::pair<int, int> now_map_cord, DIRECTION to_dir)
{
	switch (to_dir)
	{
	case DIRECTION::UP:
		now_map_cord.second = (now_map_cord.second - 1 + size_map_y) % size_map_y;
		break;
	case DIRECTION::RIGHT:
		now_map_cord.first = (now_map_cord.first + 1) % size_map_x;
		break;
	case DIRECTION::DOWN:
		now_map_cord.second = (now_map_cord.second + 1) % size_map_y;
		break;
	case DIRECTION::LEFT:
		now_map_cord.first = (now_map_cord.first - 1 + size_map_x) % size_map_x;
		break;
	case DIRECTION::UNDER:// С‚Р°Рє С…РѕСЂРѕС€Рѕ
		break;
	}
	return now_map_cord;
}

Creature* parse_str_to_Creature(const std::pair<int, int>& map_cord, std::string str)
{
	int iter = 0;

	TYPE_CREATURE type_creature = TYPE_CREATURE(parse_str_to_int_one_step(str, &iter));
	if (type_creature == TYPE_CREATURE::Void) return nullptr;

	DIRECTION dir = DIRECTION(parse_str_to_int_one_step(str, &iter));
	int age = parse_str_to_int_one_step(str, &iter), energy = parse_str_to_int_one_step(str, &iter), br_iter = parse_str_to_int_one_step(str, &iter), br_size = parse_str_to_int_one_step(str, &iter);

	std::vector<Action*> br;
	br.reserve(br_size);
	for (int i = 0; i < br_size; i++)
	{
		int arr[5]{};
		for (int j = 0; j < 5; j++)
		{
			arr[j] = parse_str_to_int_one_step(str, &iter);
		}

		switch (type_creature)
		{
		case TYPE_CREATURE::Plant:
			switch (TYPE_ACTION(arr[0]))
			{
			case TYPE_ACTION::GO:
				br.push_back(new Creature_Plant::Action_go(nullptr));
				break;
			case TYPE_ACTION::EAT:
				br.push_back(new Creature_Plant::Action_eat(nullptr));
				break;
			case TYPE_ACTION::MULTIPLY:
				br.push_back(new Creature_Plant::Action_multiply(nullptr));
				break;
			case TYPE_ACTION::TURN:
				br.push_back(new Creature_Plant::Action_turn(nullptr, DIRECTION(arr[1])));
				break;
			case TYPE_ACTION::CONDITION_BY_TYPE_CREATURE:
				br.push_back(new Creature_Plant::Action_condition_by_TYPE_CREATURE(nullptr, DIRECTION(arr[1]), arr[3], arr[4], TYPE_CREATURE(arr[2])));
				break;
			case TYPE_ACTION::CONDITION_BY_CELL:
				br.push_back(new Creature_Plant::Action_condition_by_Cell(nullptr, DIRECTION(arr[1]), arr[3], arr[4], arr[2]));
				break;
			case TYPE_ACTION::CHANGE_ITER:
				br.push_back(new Creature_Plant::Action_change_iter(nullptr, arr[3]));
				break;
			default:
				throw;
			}
			break;
		case TYPE_CREATURE::Herbivore:
			switch (TYPE_ACTION(arr[0]))
			{
			case TYPE_ACTION::GO:
				br.push_back(new Creature_Herbivore::Action_go(nullptr));
				break;
			case TYPE_ACTION::EAT:
				br.push_back(new Creature_Herbivore::Action_eat(nullptr));
				break;
			case TYPE_ACTION::MULTIPLY:
				br.push_back(new Creature_Herbivore::Action_multiply(nullptr));
				break;
			case TYPE_ACTION::TURN:
				br.push_back(new Creature_Herbivore::Action_turn(nullptr, DIRECTION(arr[1])));
				break;
			case TYPE_ACTION::CONDITION_BY_TYPE_CREATURE:
				br.push_back(new Creature_Herbivore::Action_condition_by_TYPE_CREATURE(nullptr, DIRECTION(arr[1]), arr[3], arr[4], TYPE_CREATURE(arr[2])));
				break;
			case TYPE_ACTION::CONDITION_BY_CELL:
				br.push_back(new Creature_Herbivore::Action_condition_by_Cell(nullptr, DIRECTION(arr[1]), arr[3], arr[4], arr[2]));
				break;
			case TYPE_ACTION::CHANGE_ITER:
				br.push_back(new Creature_Herbivore::Action_change_iter(nullptr, arr[3]));
				break;
			default:
				throw;
			}
			break;
		case TYPE_CREATURE::Scavenger:
			switch (TYPE_ACTION(arr[0]))
			{
			case TYPE_ACTION::GO:
				br.push_back(new Creature_Scavenger::Action_go(nullptr));
				break;
			case TYPE_ACTION::EAT:
				br.push_back(new Creature_Scavenger::Action_eat(nullptr));
				break;
			case TYPE_ACTION::MULTIPLY:
				br.push_back(new Creature_Scavenger::Action_multiply(nullptr));
				break;
			case TYPE_ACTION::TURN:
				br.push_back(new Creature_Scavenger::Action_turn(nullptr, DIRECTION(arr[1])));
				break;
			case TYPE_ACTION::CONDITION_BY_TYPE_CREATURE:
				br.push_back(new Creature_Scavenger::Action_condition_by_TYPE_CREATURE(nullptr, DIRECTION(arr[1]), arr[3], arr[4], TYPE_CREATURE(arr[2])));
				break;
			case TYPE_ACTION::CONDITION_BY_CELL:
				br.push_back(new Creature_Scavenger::Action_condition_by_Cell(nullptr, DIRECTION(arr[1]), arr[3], arr[4], arr[2]));
				break;
			case TYPE_ACTION::CHANGE_ITER:
				br.push_back(new Creature_Scavenger::Action_change_iter(nullptr, arr[3]));
				break;
			default:
				throw;
			}
			break;
		default:
			throw;
		}
	}
	
	switch (type_creature)
	{
	case TYPE_CREATURE::Plant:
		return new Creature_Plant(map_cord, energy, dir, age, &br, br_iter);
	case TYPE_CREATURE::Herbivore:
		return new Creature_Herbivore(map_cord, energy, dir, age, &br, br_iter);
	case TYPE_CREATURE::Scavenger:
		return new Creature_Scavenger(map_cord, energy, dir, age, &br, br_iter);
	default:
		throw;
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



Creature::Creature(std::pair<int, int> map_cord, int energy, DIRECTION dir, int age, std::vector<Action*>* brain, unsigned int iter)
{
	this->age = age;
	this->energy = energy;
	this->iter = iter;
	this->dir = dir;
	this->map_cord = map_cord;

	this->flag_step = true;

	if (brain == nullptr) {
		this->brain_mutation((rand() % start_max_len_brain) + 1, &this->brain);
	}
	else {
		for (auto& act : *brain)
		{
			act->set_Creature(this);    // РїРѕРјРµС‚РёР» РєР°Рє СЃРІРѕР№
		}
		this->brain = *brain;    // СЃРєРѕРїРёСЂРѕРІР°Р» РјРѕР·Рі Рё С…СЂР°РЅРёС‚ РєР°Рє СЃРІРѕР№
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
		for (int i = 0; i < limit_power_step && !this->brain[this->iter]->use(); ++i) {};   // С†РёРєР» РґР»СЏ РїСЂРѕРєСЂСѓС‚РєРё РґРµР№СЃС‚РІРёР№, РЅРµ Р·Р°РІРµСЂС€Р°СЋС€РёС… С…РѕРґ 
	}

	//int tmp = 0;   // РєРѕР»РёС‡РµСЃС‚РІРѕ СЃСѓС‰РµСЃС‚РІ РјРѕРµРіРѕ РёРїР°
	//switch (this->get_TYPE_CREATURE())
	//{
	//case TYPE_CREATURE::Plant:
	//	tmp = Creature_Plant::get_type_count();
	//	break;
	//case TYPE_CREATURE::Herbivore:
	//	tmp = Creature_Herbivore::get_type_count();
	//	break;
	//case TYPE_CREATURE::Scavenger:
	//	tmp = Creature_Scavenger::get_type_count();
	//	break;
	//}
	////this->energy -= 100.0 * (CountPlant + CountScavenger + CountHerbivore) / (size_map_x * size_map_y);
	////this->energy -= int(float(limit_energy / 8) * (tmp * 2) / (size_map_x * size_map_y) + this->brain.size());
	//this->energy -= (limit_energy * PosSliderAllLose * tmp) / (size_map_x * size_map_y * 100);
	////this->energy -= int(float(limit_energy / 20) * (tmp * 4) / (size_map_x * size_map_y) + this->brain.size());
}

void Creature::allow_to_act()
{
	this->flag_step = true;
}



void Creature::build_brain(HWND hWnd)    // !!!!!!!!!!!! РЅР°Р·РІР°РЅРёРµ
{
	for (unsigned int i = this->brain.size(); i < StaticPeepBrain.size(); i++)
	{
		ShowWindow(StaticPeepBrain[i].first, SW_HIDE);
		DestroyWindow(StaticPeepBrain[i].first);
	}
	for (unsigned int i = StaticPeepBrain.size(); i < this->brain.size(); i++)
	{
		StaticPeepBrain.push_back({ CreateWindowA("STATIC", "", WS_CHILD | ES_CENTER, 0, 0, 0, 0, hWnd, NULL, NULL, NULL), 0});
	}
	StaticPeepBrain.resize(this->brain.size());


	for (unsigned int i = 0; i < this->brain.size(); i++)
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
	for (unsigned int i = 0; i < StaticPeepBrain.size(); i++)
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
		std::to_string(this->get_TYPE_CREATURE()) + ';'
		+ std::to_string(this->dir) + ';'
		+ std::to_string(this->age) + ';' 
		+ std::to_string(this->energy) + ';'
		+ std::to_string(this->iter) + ';'
		+ std::to_string(this->brain.size()) + ';';

	for (auto& act : this->brain) {
		act->write_myself(&out);
	}

	return out + '\n';
}



DIRECTION Creature::get_dir()
{
	return this->dir;
}

int Creature::get_energy()
{
	return this->energy;
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


void Creature::brain_mutation(unsigned int mut_iter, std::vector<Action*>* change_brain)  // РјСѓС‚РёСЂСѓРµС‚ РіРµРЅ РЅРѕРјСЂ mut_iter РёР»Рё РјРѕР·Рі РґРѕСЂР°СЃС‚Р°РµС‚ РґРѕ РјСѓС‚РёСЂСѓРµРјРіРѕ РіРµРЅР°
{
	if (change_brain->size() > mut_iter) {     // РµСЃР»Рё РјРµРЅСЏРµРјС‹Р№ РіРµРЅ СѓР¶Рµ СЃРѕР·РґР°РЅ
		if (rand() % 2 || !(*change_brain)[mut_iter]->mutation()) {			// РІРѕР·РјРѕР¶РЅРѕ РїРѕРјРµРЅСЏС‚СЊ С‡Р°СЃС‚СЊ РіРµРЅР°
			delete (*change_brain)[mut_iter];								// РµСЃР»Рё РЅРµ РїРѕР»СѓС‡РёР»РѕСЃСЊ, С‚Рѕ РёР·РјРµРЅРёС‚СЊ РІРµСЃСЊ РіРµРЅ
			(*change_brain)[mut_iter] = get_rand_Action(this, change_brain->size());
		}
		return;
	}
	
	while (mut_iter >= change_brain->size()) {
		change_brain->push_back(get_rand_Action(this, mut_iter));
	}
	//for (auto& act : this->brain)   // С‡С‚РѕР±С‹ СЃ Р±РѕР»СЊС€РёРј С€Р°РЅСЃРѕРј РЅР° РЅРѕРІС‹Рµ РіРµРЅС‹ СЃСЃС‹Р»Р°Р»СЃСЊ
	//{
	//	if (rand() % 2) {
	//		act->mutation();
	//	}
	//}
}

void Creature::check_my_live()
{
	if (this->energy < 0) {
		this->get_under_me()->set_Creature();
		return;
	}

	if (++this->age > limit_age) {
		//this->get_under_me()->change_free_energy(10);
		this->get_under_me()->change_free_energy(max(this->energy >> 5, 10));
		this->get_under_me()->set_Creature();
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








