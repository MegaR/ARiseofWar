#pragma once
#include "Building.h"
#include "Button.h"
#include "UnitCatapult.h"

#define SIEGEWORKSHOPCOST  0,0,0,0

class SiegeWorkshop : public Building
{
public:
	SiegeWorkshop(int tileX, int tileY, int player, Scene* scene);
	~SiegeWorkshop(void);

		
	void update();
	void createUnit();
	void addtoqueue();
	void selected();
	void deselected();
	void startTurn();

	bool enemyTurn();
	bool allowBuild();
	int buildturn;

	IGUIStaticText* txt;
	IGUIImage* GUI;
	Button* CatapultButton;
};

