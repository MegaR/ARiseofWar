#pragma once
class Entity
{
public:
	Entity(void);
	~Entity(void);

	int tileX;
	int tileY;
	int player;
	//model
	int hp;
	bool selected;

	void startTurn();
	void render();
	void endTurn();
	void update();



};

