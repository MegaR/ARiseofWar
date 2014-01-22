#pragma once
#include <vector>

#include "Scene.h"
#include "Game.h"
#include "Button.h"

class OptionsScene : public Scene
{
public:
	OptionsScene(void);
	~OptionsScene();

	void update();

private:
	IGUIImage* background;
	ISoundEngine* BGM;
};