#pragma once

#include "Unit.h"
#include "Barracks.h"
#include "Button.h"
#include "LumberMill.h"
#include "Quarry.h"
#include "Farm.h"
#include "SiegeWorkshop.h"

#include "TileForest.h"
#include "TileGrass.h"

#define PEASANTBUILDTIME 1
#define PEASANTCOST 5, 10, 0, 5

class UnitPeasant: public Unit
{
public:
	UnitPeasant(int _x, int _y, int _player, Scene* scene);
	~UnitPeasant();

	void update();
	void selected();
	void deselected();
	virtual bool enemyTurn();
	bool attemptBuildBarracks();
	bool attemptBuildLumberMill();
	void buildLumberMill(int tileX, int tileY);
	bool attemptBuildQuarry();
	void buildQuarry(int tileX, int tileY);
	bool attemptBuildFarm();
	void buildFarm(int tileX, int tileY);
	bool attemptBuildSiegeWorkshop();
	void buildSiegeWorkshop(int tileX,int tileY);
	bool reasonableSpace();

	IGUIImage* GUI;
	Button* buildBarracksButton;
	Button* buildLumberMillButton;
	Button* buildQuarryButton;
	Button* buildFarmButton;
	Button* buildSiegeWorkshopButton;
};

