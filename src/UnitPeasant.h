#pragma once

#include "Unit.h"
#include "Barracks.h"
#include "Button.h"

class UnitPeasant: public Unit
{
public:
	UnitPeasant(int _x, int _y, int _player);
	~UnitPeasant();

	void update();
	void buildBuilding();
	void selected();
	void deselected();
	virtual void enemyTurn();

	bool showGUI, isSelected, buildingBuilt;
	IGUIImage* GUI;
	Button* buildBarracksButton;
};

