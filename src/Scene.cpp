#include "Scene.h"
#include "Game.h"
Scene::Scene() {

}

Scene::~Scene() {

}


void Scene::Click (){
	Game* game = &Game::getInstance();
	vector2d<s32> mousePosition = game->device->getCursorControl()->getPosition();
	int x = mousePosition.X;
	int y = mousePosition.Y;
	
	position2d<s32> *pos = new position2d<s32>(mousePosition.X,mousePosition.Y);

	ICameraSceneNode* camera = Game::getInstance().camera;
	
	line3d<f32> *line3d_trace = new line3d<f32>;
	*line3d_trace=game->sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(*pos,camera);

	scene::ISceneNode *nodeline = game->sceneManager->getSceneCollisionManager()->getSceneNodeFromRayBB(*line3d_trace,0x1,false);

}

void Scene::start(){


}

void Scene::update(){


}

void Scene::render(){


}
