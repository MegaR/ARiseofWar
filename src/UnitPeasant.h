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

#define MINWOOD 30
#define MINFOOD 30
#define MINSTONE 30
#define MINGOLD 30

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
	bool reasonableSpace(int tileX, int tileY);

	IGUIImage* GUI;
	Button* buildBarracksButton;
	Button* buildLumberMillButton;
	Button* buildQuarryButton;
	Button* buildFarmButton;
	Button* buildSiegeWorkshopButton;
};

