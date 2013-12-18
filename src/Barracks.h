#pragma once
#include "building.h"
#include "UnitKnight.h"
#include "Button.h"

class Barracks : public Building
{
public:
	Barracks(int tileX, int tileY, int player);
	~Barracks(void);
	
	void update();
	void createUnit();
	void addtoqueue();
	void selected();
	void deselected();
	void startTurn();

	bool allowBuild;
	int buildturn;

	IGUIStaticText* txt;
	IGUIImage* GUI;
};

