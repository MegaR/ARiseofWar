#pragma once

#include <iostream>
using namespace std;

class Player
{
public:
	Player(void);
	~Player(void);

	virtual void startTurn();
	virtual void endTurn();

	bool hasResources(int wood, int food, int gold, int stone);
	void useResources(int wood, int food, int gold, int stone);
	int wood;
	int food;
	int gold;
	int stone;
};

