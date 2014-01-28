#pragma once

#include <ISceneCollisionManager.h>
#include <irrKlang.h>
using namespace irrklang;

class Scene
{
public:
	Scene(void);
	virtual ~Scene(void);

	virtual void Click();
	virtual void start();
	virtual void update();
	virtual void render();
protected:
	ISound* music;
};
