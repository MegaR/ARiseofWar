#pragma once
#include "building.h"
#include "button.h"

#define PEASANTBUILDTIME 2
#define PEASANTCOST 10, 0, 0, 0

class TownCenter :
	public Building
{
public:
	TownCenter(int tileX, int tileY, int player, Scene* scene);
	~TownCenter(void);

	void update();
	void createUnit();
	void addtoqueue();
	void selected();
	void deselected();
	void startTurn();
	void enemyTurn();

	bool allowBuild();
	int buildturn;

	IGUIStaticText* txt;
	IGUIImage* GUI;
	Button* peasantButton;
};

