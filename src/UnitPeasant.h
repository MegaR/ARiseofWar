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
#define PEASANTCOST 5, 10, 5, 0

//AI
#define MINWOOD 40
#define MINFOOD 40
#define MINSTONE 40
#define MINGOLD 40
#define BARRACKSSIEGERATIO 2

class UnitPeasant: public Unit
{
public:
	UnitPeasant(int _x, int _y, int _player, Scene* scene);
	~UnitPeasant();

	void update();
	void selected();
	void deselected();
	bool attemptBuildBarracks();
	bool attemptBuildLumberMill();
	void buildLumberMill(int tileX, int tileY);
	bool attemptBuildQuarry();
	void buildQuarry(int tileX, int tileY);
	bool attemptBuildFarm();
	void buildFarm(int tileX, int tileY);
	bool attemptBuildSiegeWorkshop();
	void buildSiegeWorkshop(int tileX,int tileY);

	virtual bool enemyTurn();
	bool resourceBuilding();
	vector2d<int> findWheat();
	vector2d<int> findStone();
	vector2d<int> findForest();
	void gotoClearing();
	bool reasonableSpace(int tileX, int tileY);
	float barracksSiegeRatio();

	IGUIImage* GUI;
	Button* buildBarracksButton;
	Button* buildLumberMillButton;
	Button* buildQuarryButton;
	Button* buildFarmButton;
	Button* buildSiegeWorkshopButton;
};

