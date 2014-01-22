#pragma once

#include <iostream>
using namespace std;

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Button
{
public:
	Button(int x, int y, int w, int h, std::string t, std::string tt, ITexture* _img = NULL);
	~Button();

	IGUIButton* btn;
	ITexture* img;
	bool pressed, updated;

	void update();
	//virtual void onClick(){};
};