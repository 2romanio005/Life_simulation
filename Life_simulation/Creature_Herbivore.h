#pragma once
#include "Creatures.h"

class Creature_Herbivore : public Creature {
public:
	Creature_Herbivore(std::pair<int, int> map_cord, int energy, DIRECTION dir, int age = 0, std::vector<Action*>* brain = nullptr, unsigned int iter = 0);

	Creature* copy(std::pair<int, int> map_cord) override;

	~Creature_Herbivore() override;

	void step() override;

	void draw_myself(HDC hdc, std::pair<int, int> cord) override;

	static int get_type_count();

	TYPE_CREATURE get_TYPE_CREATURE() override;

	void brain_mutation(std::vector<Action*>* change_brain, unsigned int mut_iter) override;
private:
	static int CountHarbivore;
	
	Action* get_rand_Action(Creature* creature, unsigned int max_iter) override;

public:
	class Action_go : public Action_go_global {
	public:
		Action_go(Creature_Herbivore* creature);

		bool use() override;

		Action* copy() override;
	};

	class Action_eat : public Action_eat_global {
	public:
		Action_eat(Creature_Herbivore* creature);

		bool use() override;

		Action* copy() override;
	};

	class Action_multiply : public Action_multiply_global {
	public:
		Action_multiply(Creature_Herbivore* creature);

		bool use() override;

		Action* copy() override;
	};

	class Action_turn : public Action_turn_global {
	public:
		Action_turn(Creature_Herbivore* creature, DIRECTION to_dir);

		//bool use() override;

		Action* copy() override;
	};

	class Action_condition_by_TYPE_CREATURE : public Action_condition_by_TYPE_CREATURE_global {
	public:
		Action_condition_by_TYPE_CREATURE(Creature_Herbivore* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, TYPE_CREATURE type_creature);

		//bool use() override;

		Action* copy() override;
	};

	class Action_condition_by_Cell_energy : public  Action_condition_by_Cell_energy_global {
	public:
		Action_condition_by_Cell_energy(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit);

		//bool use() override;

		Action* copy() override;
	};

	class Action_condition_by_Creature_energy : public  Action_condition_by_Creature_energy_global {
	public:
		Action_condition_by_Creature_energy(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit);

		//bool use() override;

		Action* copy() override;
	};

	class Action_change_iter : public Action_change_iter_global {
	public:
		Action_change_iter(Creature_Herbivore* creature, unsigned int iter);

		bool use() override;

		Action* copy() override;
	};
};
