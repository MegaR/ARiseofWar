#pragma once

#include "Unit.h"

#define SPEARMANCOST 0, 10, 5, 5
#define SPEARMANBUILDTIME 1

class UnitSpearman: public Unit
{
public:
	UnitSpearman(int _x, int _y, int _player, Scene* scene);
	~UnitSpearman();
	
	void selected();
	void update();
	void startTurn();
private:
	bool usplayed;
};

