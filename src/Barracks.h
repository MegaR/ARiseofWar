#pragma once
#include "Building.h"
#include "UnitKnight.h"
#include "UnitArcher.h"
#include "Button.h"

#define BARRACKSCOST 10, 20, 10, 10

class Barracks : public Building
{
public:
	Barracks(int tileX, int tileY, int player, Scene* scene);
	~Barracks(void);
	
	void update();
	void createUnit();
	void addtoqueue();
	void selected();
	void deselected();
	void startTurn();
	bool enemyTurn();

	int buildturn;
	int creatingUnit;

	bool allowBuildKnight();
	bool allowBuildArcher();
	//bool allowBuildSpearman();
	
	IGUIImage* GUI;

	IGUIStaticText* knightTXT;
	IGUIStaticText* archerTXT;
	//IGUIStaticText* spearmanTXT;
	

	Button* knightButton;
	Button* archerButton;
	//Button* spearmanButton;
};

