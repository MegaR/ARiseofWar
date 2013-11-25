#pragma once
#include <vector>

#include "Scene.h"
#include "Game.h"
#include "Button.h"

class MenuScene : public Scene
{
public:
	MenuScene(void);
	~MenuScene(void);

	void update();
};

