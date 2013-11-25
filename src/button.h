#pragma once
#include <string.h>
#include "Game.h"

class Button
{
public:
	Button(int x, int y, int w, int h, std::string t);
	~Button(void);

	IGUIButton* btn;
	bool pressed;

	void update();
	//virtual void onClick(){};
};