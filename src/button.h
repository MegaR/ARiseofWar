#pragma once

#include <string.h>
#include "Game.h"

class Button
{
public:
	Button(int x, int y, int w, int h, std::string t, ITexture* _img = NULL);
	~Button();

	IGUIButton* btn;
	ITexture* img;
	bool pressed, updated;

	void update();
	//virtual void onClick(){};
};