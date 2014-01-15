#pragma once

#include "Unit.h"
#include "Barracks.h"
#include "Button.h"

#define PEASANTBUILDTIME 2
#define PEASANTCOST 10, 0, 0, 0

class UnitPeasant: public Unit
{
public:
	UnitPeasant(int _x, int _y, int _player, Scene* scene);
	~UnitPeasant();

	void update();
	void selected();
	void deselected();
	virtual void enemyTurn();
	bool attemptBuildBarracks();
	bool reasonableSpace();

	bool showGUI, isSelected, buildingBuilt;
	IGUIImage* GUI;
	Button* buildBarracksButton;
};

