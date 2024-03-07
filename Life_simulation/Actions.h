#pragma once
#include "Definition.h"


enum Type_Action
{
	GO,
	EAT,
	TURN,
	CONDITION_BY_TYPE_CREATURE,
	CONDITION_BY_CELL,
	CHANGE_ITER
};


class Action {
public:
	Action(Creature* creature);

	virtual bool use() = 0;

	virtual bool mutation();

	virtual Action* copy() = 0;

	virtual std::string* draw_myself() = 0;
	virtual void write_myself(std::string* out) = 0;

	virtual Type_Action get_Type_Action() = 0;

	void set_Creature(Creature* creature);

	std::pair<std::string, int>* build_draw();
protected:
	Creature* creature;
};


class Action_go : public Action {
public:
	Action_go(Creature* creature);

	bool use() override;

	Action* copy() override;

	std::string* draw_myself() override;
	void write_myself(std::string* out) override;

	Type_Action get_Type_Action() override;
};

class Action_eat : public Action {
public:
	Action_eat(Creature* creature);

	bool use() override;

	Action* copy() override;

	std::string* draw_myself() override;
	void write_myself(std::string* out) override;

	Type_Action get_Type_Action() override;
};


class Action_turn : public Action {
public:
	Action_turn(Creature* creature, Direction to_dir);
	
	bool use() override;

	bool mutation() override;
	
	Action* copy() override;

	std::string* draw_myself() override;
	void write_myself(std::string* out) override;

	Type_Action get_Type_Action() override;
private:
	Direction to_dir;
};

class Action_condition_by_Type_Creature : public Action {
public:
	Action_condition_by_Type_Creature(Creature* creature, Direction to_dir, unsigned int true_iter, unsigned int false_iter,  Type_Creature type_creature);

	bool use() override;

	bool mutation() override;

	Action* copy() override;

	std::string* draw_myself() override;
	void write_myself(std::string* out) override;

	Type_Action get_Type_Action() override;
private:
	Direction to_dir;
	Type_Creature type_creature;

	unsigned int true_iter;
	unsigned int false_iter;
};

class Action_condition_by_Cell : public Action {
public:
	Action_condition_by_Cell(Creature* creature, Direction to_dir, unsigned int true_iter, unsigned int false_iter, int limit/*, bool (*cond)(int one, int two)*/);

	bool use() override;

	bool mutation() override;

	Action* copy() override;

	std::string* draw_myself() override;
	void write_myself(std::string* out) override;

	Type_Action get_Type_Action() override;
private:
	Direction to_dir;
	int limit;
	//bool (*cond)(int one, int two);

	unsigned int true_iter;
	unsigned int false_iter;
};

class Action_change_iter : public Action {
public:
	Action_change_iter(Creature* creature, unsigned int iter);

	bool use() override;

	bool mutation() override;

	Action* copy() override;

	std::string* draw_myself() override;
	void write_myself(std::string* out) override;

	Type_Action get_Type_Action() override;
private:
	unsigned int iter;
};


