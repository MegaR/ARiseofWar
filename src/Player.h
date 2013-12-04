#pragma once
class Player
{
public:
	Player(void);
	~Player(void);

	virtual void startTurn();
	virtual void endTurn();

};

