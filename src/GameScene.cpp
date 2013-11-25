#include "GameScene.h"

GameScene::GameScene() {
	moveCamera(0,0,0);
}

GameScene::~GameScene() {

}

void GameScene::update() {
	updateMouse();
}

void GameScene::turn(){

}

void GameScene::updateMouse() {
	Game* game = &Game::getInstance();
	vector2d<s32> mousePosition = game->device->getCursorControl()->getPosition();
	int x = mousePosition.X;
	if (x < 0) {x = 0;}
	if (x >	game->screenWidth) {x = game->screenWidth;}

	int y = mousePosition.Y;
	if (y < 0) {y = 0;}
	if (y >	game->screenHeight) {y = game->screenHeight;}

	//cout << "MousePosition: X=" << x << "Y=" << y << endl;
	
	if(x < 10) {
		moveCamera(-100 * game->delta, 0, 0);
	}
	if(x > game->screenWidth-10) {
		moveCamera(100 * game->delta, 0, 0);
	}
	if(y < 10) {
		moveCamera(0,0,100 * game->delta);
	}
	if(y > game->screenHeight-10) {
		moveCamera(0,0,-100 * game->delta);
	}

		//Game* game = &Game::getInstance();
		//vector2d<s32> mousePosition = game->device->getCursorControl()->getPosition();
		//int x = mousePosition.X;
		//int y = mousePosition.Y;
	
		position2d<s32> *pos = new position2d<s32>(mousePosition.X,mousePosition.Y);

		ICameraSceneNode* camera = Game::getInstance().camera;
	
		line3d<f32> *line3d_trace = new line3d<f32>;
		*line3d_trace=game->sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(*pos,camera);

		scene::ISceneNode *nodeline = game->sceneManager->getSceneCollisionManager()->getSceneNodeFromRayBB(*line3d_trace,0x1,false);
		cout << "the cake is not a lie" << endl;
}

void GameScene::moveCamera(float x, float y, float z) {
	ICameraSceneNode* camera = Game::getInstance().camera;
	vector3df position = camera->getPosition();
	position.X += x;
	position.Y += y;
	position.Z += z;
	camera->setPosition(position);

	position.Y += -1;
	position.Z += 0.5f;
	camera->setTarget(position);
}