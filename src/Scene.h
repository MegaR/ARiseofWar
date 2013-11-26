#pragma once

#include <ISceneCollisionManager.h>


class Scene
{
public:
	Scene(void);
	virtual ~Scene(void);

	virtual void Click();
	virtual void start();
	virtual void update();
	virtual void render();
	
};
