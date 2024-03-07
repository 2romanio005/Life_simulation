#include "Cell.h"
#include "MainConnection.h"



Cell* get_Cell_by_map_cord(const std::pair<int, int>& map_cord)
{
	return &map[map_cord.first][map_cord.second];
}






Cell::Cell(Creature* creature)
{
	this->free_energy = 0;
	//this->solar_energy = 0;
	this->creature = creature;
}

Cell::~Cell()
{
	set_Creature();
}

void Cell::Creature_step()
{
	if (this->creature != nullptr) {
		this->creature->step();
	}
}

void Cell::Creature_one_step_finish()
{
	if (this->creature != nullptr) {
		this->creature->one_step_finish();
	}
}

void Cell::draw_myself(HDC hdc)
{
	//SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
	//SelectObject(hdc, H_Gray[0]);
	//SelectObject(hdc, (HGDIOBJ)NULL_PEN);
	std::pair<int, int> cord(this->map_cord.first * size_cell, this->map_cord.second * size_cell);

	SelectObject(hdc, P_Null);
	SelectObject(hdc, H_Gray[min(this->free_energy / (limit_energy / 200), 199)]);
	Rectangle(hdc, cord.first, cord.second, cord.first + size_cell + 1, cord.second + size_cell + 1);

	if (this->creature != nullptr) {
		this->creature->draw_myself(hdc, cord);

		if (this->creature == peep_Creature) {
			int r = int(size_cell * 0.25);
			cord.first += size_half_cell; cord.second += size_half_cell;
			SelectObject(hdc, H_Gray[0]);
			RoundRect(hdc, cord.first - r, cord.second - r, cord.first + r, cord.second + r, r * 2, r * 2);
		}
	}
}

std::string Cell::write_myself()
{
	std::string out = std::to_string(this->free_energy) + ';';
	if (this->creature == nullptr) {
		out += std::to_string(Type_Creature::Void) + ";\n";
	}
	else {
		out += this->creature->write_myself();
	}
	return out;
}

void Cell::read_myself(std::string str)
{
	int iter = 0;

	this->change_free_energy(parse_str_to_int_one_step(str, &iter) - this->free_energy);

	str.erase(0, iter);
	iter = 0;
	this->set_Creature(parse_str_to_Creature(this->map_cord, str));
}


Type_Creature Cell::get_Type_Creature()
{
	if (this->creature != nullptr) {
		return (this->creature->get_Type_Creature());
	}
	return Type_Creature::Void;
}

int Cell::get_Creature_energy()
{
	return this->creature->get_energy();
}

Creature* Cell::get_Creature()
{
	return this->creature;
}

void Cell::change_free_energy(int step)
{
	this->free_energy = this->free_energy + step;
	if (this->free_energy < 0) this->free_energy = 0;
}

void Cell::set_Creature(Creature* creature)
{
	if (this->creature != nullptr) {
		if (this->creature != peep_Creature) {
			delete this->creature;
		}
		else {
			life_peep_Creature = false;
		}
	}
	this->creature = creature;
}

void Cell::swap_Creapure(Cell* cell)
{
	Creature* tmp = this->creature;

	this->creature = cell->creature;
	cell->creature = tmp;
}

void Cell::set_map_cord(std::pair<int, int> map_cord)
{
	this->map_cord = map_cord;
}

int Cell::get_free_energy()
{
	return this->free_energy;
}

std::pair<int, int> Cell::get_map_cord()
{
	return this->map_cord;
}













//#include "Cell.h"
//
//Cell::Cell()
//{
//	this->free_energy = 0;
//	this->creature = nullptr/*(Creature*)new Creature_Plant*/;
//}
//
//Cell::~Cell()
//{
//	this->set_creature();
//}
//
//
////void Cell::set_creature(Creature* creature)
////{
////	if (this->creature != nullptr) {
////		delete this->creature;
////	}
////	this->creature = creature;
////}
//
//void Cell::creature_step()
//{
//	(this->creature)->get_Type_Creature();
//}
//
////Creature* Cell::get_creature()
////{
////	return this->creature;
////}
