#pragma once

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void Click(int x, int  y);
	void start();
	void update();
	void render();
	
};
