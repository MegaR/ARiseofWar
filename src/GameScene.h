#pragma once
#include <vector>

#include "Entity.h"
#include "TileSystem.h"
#include "Scene.h"
#include "Button.h"

#include "Game.h"

class GameScene : public Scene
{
public:
	GameScene(void);
	~GameScene(void);

	TileSystem tilesystem;
	std::vector<Entity> entities;
	int turnCount;

	void turn();
	void update();
	void updateMouse();
	void mouseRay();
	
private:
	void moveCamera(float x, float y, float z);
};