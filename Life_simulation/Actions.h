#pragma once
#include "Definition.h"


class Action {
public:
	Action(Creature* creature);

	virtual bool use() = 0;

	virtual bool mutation();

	virtual Action* copy() = 0;

	virtual std::string* draw_myself() = 0;
	virtual void write_myself(std::string* out);

	virtual TYPE_ACTION get_TYPE_ACTION() = 0;

	void set_Creature(Creature* creature);

	std::pair<std::string, int>* build_draw();
protected:
	Creature* creature;
};








