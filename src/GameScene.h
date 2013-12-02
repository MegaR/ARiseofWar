#pragma once
#include <vector>

#include "Entity.h"
#include "TileSystem.h"
#include "Scene.h"
#include "Button.h"
#include "Player.h"
#include "EnemyPlayer.h"

#include "Game.h"

class GameScene : public Scene
{
public:
	GameScene(void);
	~GameScene(void);

	TileSystem tilesystem;
	std::vector<Entity*> entities;
	int turnCount;
	Entity *storedEntity;
	

	void nextTurn();
	void update();
	void updateMouse();
	void clickEntity();
	vector2d<int> mouseRay();
	Entity* getEntity(int x, int y);
	std::vector<vector2d<int>>* findPath(vector2d<int> start, vector2d<int> end);
	

private:
	void moveCamera(float x, float y, float z);

	//pathfinding
	int findElement(std::vector<vector2d<int>> list, vector2d<int> element); 
	vector2d<int> lowest(int list[][MAPSIZE]);
	std::vector<vector2d<int>>* get_neighbors(vector2d<int> current);
	int heuristic_cost_estimate(vector2d<int> current, vector2d<int> goal);
	std::vector<vector2d<int>>* reconstructed_path(vector2d<int> came_from[][MAPSIZE], vector2d<int> end, vector2d<int> start);

	IMeshSceneNode *selectedNode;

	Player* players[2];
	int currentPlayer;
};