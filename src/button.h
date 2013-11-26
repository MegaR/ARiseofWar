#pragma once

#include <string.h>
#include "Game.h"

class Button
{
public:
	Button(int x, int y, int w, int h, std::string t, ITexture* _img);
	~Button();

	IGUIButton* btn;
	ITexture* img;
	bool pressed;

	void update();
	//virtual void onClick(){};
};