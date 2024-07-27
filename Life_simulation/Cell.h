#pragma once
#include "Definition.h"



class Cell
{
public:
	Cell(Creature* creature = nullptr);

	~Cell();

	void Creature_step();

	void Creature_allow_to_act();

	void draw_myself(HDC hdc);
	std::string write_myself();

	void read_myself(std::string str);

	void change_free_energy(int step);

	void set_free_energy(int free_energy);

	void set_Creature(Creature* creature = nullptr);

	void swap_Creapure(Cell* cell);

	void set_map_cord(std::pair<int, int> map_cord);


	int get_free_energy();
	std::pair<int, int> get_map_cord();
	TYPE_CREATURE get_TYPE_CREATURE();
	int get_Creature_energy();
	Creature* get_Creature();

	//int solar_energy;
private:
	int free_energy;

	std::pair<int, int> map_cord;

	Creature* creature;
};



