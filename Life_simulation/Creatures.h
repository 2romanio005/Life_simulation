#pragma once
#include "Definition.h"



enum Type_Creature
{
	Plant,
	Herbivore,
	Scavenger,

	Void
};

enum Direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,

	UNDER = 4,

	to_FORWARD = -4,
	to_RIGHT = -3,
	to_LEFT = -1,
	to_BACK = -2
};




class Creature
{
public:
	Creature(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age = 0, std::vector<Action*>* brain = nullptr, unsigned int iter = 0);

	virtual ~Creature();

	virtual Creature* copy(std::pair<int, int> map_cord) = 0;

	void step();

	void one_step_finish();

	virtual void draw_myself(HDC hdc, std::pair<int, int> cord) = 0;

	void build_brain(HWND hWnd);
	void draw_brain();
	std::string write_myself();

	//virtual int get_type_count() = 0;

	Direction get_dir();

	int get_energy();

	int get_lim_energy();

	int get_age();

	int get_iter();

	int get_brain_size();

	virtual Type_Creature get_Type_Creature() = 0;

protected:
	void create_Action(unsigned int mut_iter, std::vector<Action*>* brain);

	Cell* get_under_me();

	void next_iter();

	int age;
	int energy;
	int lim_energy;
	unsigned int iter;

	std::vector<Action*> brain;

	Direction dir;
	std::pair<int, int> map_cord;

	bool flag_step;
	
	friend class Action_go;
	friend class Action_eat;
	friend class Action_turn;
	friend class Action_condition_by_Type_Creature;
	friend class Action_condition_by_Cell;
	friend class Action_change_iter;
};




class Creature_Plant : public Creature {
public:
	Creature_Plant(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age = 0, std::vector<Action*>* brain = nullptr, unsigned int iter = 0);

	~Creature_Plant() override;

	Creature* copy(std::pair<int, int> map_cord) override;

	//void step() override;

	void draw_myself(HDC hdc, std::pair<int, int> cord) override;

	static int get_type_count();

	Type_Creature get_Type_Creature() override;
private:
	static int CountPlant;
};


class Creature_Herbivore : public Creature {
public:
	Creature_Herbivore(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age = 0, std::vector<Action*>* brain = nullptr, unsigned int iter = 0);

	Creature* copy(std::pair<int, int> map_cord) override;

	~Creature_Herbivore() override;

	//void step() override;

	void draw_myself(HDC hdc, std::pair<int, int> cord) override;

	static int get_type_count();

	Type_Creature get_Type_Creature() override;
private:
	static int CountHarbivore;
};


class Creature_Scavenger : public Creature {
public:
	Creature_Scavenger(std::pair<int, int> map_cord, int energy, int lim_energy, Direction dir, int age = 0, std::vector<Action*>* brain = nullptr, unsigned int iter = 0);

	Creature* copy(std::pair<int, int> map_cord) override;

	~Creature_Scavenger() override;

	//void step() override;

	void draw_myself(HDC hdc, std::pair<int, int> cord) override;

	static int get_type_count();

	Type_Creature get_Type_Creature() override;
private:
	static int CountScavenger;
};








