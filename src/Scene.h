#pragma once

class Scene
{
public:
	Scene(void);
	~Scene(void);

	virtual void Click(int x, int  y);
	virtual void start();
	virtual void update();
	virtual void render();
	
};
