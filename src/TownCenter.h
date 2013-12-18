#pragma once
#include "building.h"
class TownCenter :
	public Building
{
public:
	TownCenter(int tileX, int tileY, int player);
	~TownCenter(void);

	void update();
	void createUnit();
	void addtoqueue();
	void selected();
	void deselected();
	void startTurn();
	void enemyTurn();

	bool allowBuild;
	int buildturn;

	IGUIStaticText* txt;
	IGUIImage* GUI;
};

