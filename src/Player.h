#pragma once

#include <string>
#include <iostream>
using namespace std;

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace gui;

class Player
{
public:
	Player(void);
	~Player(void);
	
	IGUIImage* topRight;

	virtual void startTurn();
	virtual void update();
	virtual void endTurn();

	void createGui();

	bool hasResources(int wood, int food, int gold, int stone);
	void useResources(int wood, int food, int gold, int stone);
private:
	IGUIImage* topLeft;
	IGUIImage* woodIcon;
	IGUIImage* foodIcon;
	IGUIImage* goldIcon;
	IGUIImage* stoneIcon;
	IGUIStaticText* woodText;
	IGUIStaticText* foodText;
	IGUIStaticText* goldText;
	IGUIStaticText* stoneText;

	int wood;
	int food;
	int gold;
	int stone;
};

