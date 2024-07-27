#pragma once
#include "Definition.h"

#include "Actions.h"
#include "Cell.h"

//#include "Creature_Plant.h"
//#include "Creature_Herbivore.h"
//#include "Creature_Scavenger.h"



class Creature
{
public:
	Creature(std::pair<int, int> map_cord, int energy, DIRECTION dir, int age = 0, std::vector<Action*>* brain = nullptr, unsigned int iter = 0);

	virtual ~Creature();

	virtual Creature* copy(std::pair<int, int> map_cord) = 0;

	virtual void step() = 0;

	void allow_to_act();

	virtual void draw_myself(HDC hdc, std::pair<int, int> cord) = 0;

	void build_brain(HWND hWnd);
	void draw_brain();
	std::string write_myself();

	
	DIRECTION get_dir();
	int get_energy();
	int get_age();
	int get_iter();
	int get_brain_size();
	virtual TYPE_CREATURE get_TYPE_CREATURE() = 0;

protected:
	void check_my_live();

	void make_act();

	virtual void brain_mutation(std::vector<Action*>* brain, unsigned int mut_iter) = 0;

	virtual Action* get_rand_Action(Creature* creature, unsigned int max_iter) = 0;

	Cell* get_under_me();

	void next_iter();

	int age;
	int energy;
	unsigned int iter;

	std::vector<Action*> brain;

	DIRECTION dir;
	std::pair<int, int> map_cord;

	bool flag_step;
	

	class Action_go_global : public Action {
	public:
		Action_go_global(Creature* creature);

		virtual bool use() = 0;

		Action* copy() = 0;

		std::string* draw_myself() override;

		TYPE_ACTION get_TYPE_ACTION() override;
	};

	class Action_eat_global : public Action {
	public:
		Action_eat_global(Creature* creature);

		virtual bool use() = 0;

		virtual Action* copy() = 0;

		std::string* draw_myself() override;

		TYPE_ACTION get_TYPE_ACTION() override;
	};

	class Action_multiply_global : public Action {
	public:
		Action_multiply_global(Creature* creature);

		virtual bool use() = 0;

		virtual Action* copy() = 0;

		std::string* draw_myself() override;

		TYPE_ACTION get_TYPE_ACTION() override;
	};

	class Action_turn_global : public Action {
	public:
		Action_turn_global(Creature* creature, DIRECTION to_dir);

		bool use() override;

		bool mutation() override;

		virtual Action* copy() = 0;

		std::string* draw_myself() override;
		void write_myself(std::string* out) override;

		TYPE_ACTION get_TYPE_ACTION() override;
	protected:
		DIRECTION to_dir;
	};

	class Action_condition_by_TYPE_CREATURE_global : public Action {
	public:
		Action_condition_by_TYPE_CREATURE_global(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, TYPE_CREATURE type_creature);

		bool use() override;

		bool mutation() override;

		virtual Action* copy() = 0;

		std::string* draw_myself() override;
		void write_myself(std::string* out) override;

		TYPE_ACTION get_TYPE_ACTION() override;
	protected:
		DIRECTION to_dir;
		TYPE_CREATURE type_creature;

		unsigned int true_iter;
		unsigned int false_iter;
	};

	class Action_condition_by_Cell_energy_global : public Action {
	public:
		 Action_condition_by_Cell_energy_global(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit);

		bool use() override;

		bool mutation() override;

		virtual Action* copy() = 0;

		std::string* draw_myself() override;
		void write_myself(std::string* out) override;

		TYPE_ACTION get_TYPE_ACTION() override;
	protected:
		DIRECTION to_dir;
		int limit;

		unsigned int true_iter;
		unsigned int false_iter;
	};

	class Action_condition_by_Creature_energy_global : public Action {
	public:
		Action_condition_by_Creature_energy_global(Creature* creature, DIRECTION to_dir, unsigned int true_iter, unsigned int false_iter, int limit);

		bool use() override;

		bool mutation() override;

		virtual Action* copy() = 0;

		std::string* draw_myself() override;
		void write_myself(std::string* out) override;

		TYPE_ACTION get_TYPE_ACTION() override;
	protected:
		DIRECTION to_dir;
		int limit;

		unsigned int true_iter;
		unsigned int false_iter;
	};

	class Action_change_iter_global : public Action {
	public:
		Action_change_iter_global(Creature* creature, unsigned int iter);

		virtual bool use() = 0;

		bool mutation() override;

		virtual Action* copy() = 0;

		std::string* draw_myself() override;
		void write_myself(std::string* out) override;

		TYPE_ACTION get_TYPE_ACTION() override;
	protected:
		unsigned int iter;
	};

};
















