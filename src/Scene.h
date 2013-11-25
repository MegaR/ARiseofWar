#pragma once

#include <ISceneCollisionManager.h>


class Scene
{
public:
	Scene(void);
	~Scene(void);

	virtual void Click();
	virtual void start();
	virtual void update();
	virtual void render();
	
};
