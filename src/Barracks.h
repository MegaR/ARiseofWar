#pragma once
#include "Building.h"
#include "UnitKnight.h"
#include "UnitArcher.h"
#include "Button.h"

#define BARRACKSCOST 0, 0, 0, 10

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
	void enemyTurn();

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

