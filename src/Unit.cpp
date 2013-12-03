#include "Unit.h"

#include "Game.h"
#include <iostream>
using namespace std;

Unit::Unit(int tileX, int tileY, int player)
{
	this->tileX = tileX;
	this->tileY = tileY;
	this->player = player;

	node = Game::getInstance().sceneManager->addEmptySceneNode(0, 0);
	node->setPosition(vector3df(tileX * 10, 0, tileY * 10) );
}

Unit::~Unit()
{
	cout << "destroying Unit" << endl;
	while(modelNodes.size() > 0) {
		removeModel();
	}
}

void Unit::selected() {
	
	if(player == 0) {
		addDistanceTiles(tileX, tileY, maxDistance);
	}
}

void Unit::addDistanceTiles(int x, int y, int distance) {
	Game* game = &Game::getInstance();
	GameScene* scene = (GameScene*)game->currentScene;

	if(distance < 0) return;
	if(x < 0 || x > MAPSIZE-1) {
		return;
	}
	if(y < 0 || y > MAPSIZE-1) {
		return;
	}

	Entity* entity = scene->getEntity(x,y);
	if( entity != NULL && entity != this ) {
		return;
	}

	bool alreadyThere = false;
	for(int i = 0; i < distanceTiles.size(); i++) {
		if(distanceTiles.at(i)->getPosition().X == x*10 
			&& distanceTiles.at(i)->getPosition().Z == y*10) {
				alreadyThere = true;
		}
	}

	bool inAttackRange = false;
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities.at(i)->player == 0) continue;
		if(scene->entities.at(i)->inAttackRange(x, y, attackDistance) ) {
			inAttackRange = true;
		}
	}

	if(!alreadyThere) {
		IAnimatedMesh* model = game->sceneManager->getMesh("res/distance_Tile.3ds");
		ISceneNode* node = game->sceneManager->addMeshSceneNode(model);
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		if(inAttackRange) {
			node->setMaterialTexture( 0, game->videoDriver->getTexture("res/distance_Tile_red.png") );
		} else {
			node->setMaterialTexture( 0, game->videoDriver->getTexture("res/distance_Tile_blue.png") );
		}
		node->setPosition(vector3d<f32>(x*10, 0, y*10) );
		node->setID(0);
		distanceTiles.push_back(node);
	}

	addDistanceTiles(x-1, y, distance-1);
	addDistanceTiles(x+1, y, distance-1);
	addDistanceTiles(x, y-1, distance-1);
	addDistanceTiles(x, y+1, distance-1);
}

void Unit::deselected() {
	while(distanceTiles.size() > 0) {
		distanceTiles.at(distanceTiles.size()-1)->remove();
		distanceTiles.pop_back();
	}
}

void Unit::moveTo(int desX, int desY)
{
	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	vector<vector2d<int>>* newPath = scene->findPath(vector2d<s32>(tileX, tileY), vector2d<s32>(desX, desY) );
	if(!newPath) return;
	if(newPath->size() > maxDistance) return;

	while(newPath->size() > 0) {
		path.push_back( newPath->at(newPath->size()-1) );
		newPath->pop_back();
	}
	delete newPath;

	tileX = desX;
	tileY = desY;
}

void Unit::update() {
	if(path.size() > 0) {
		followPath();
	}
}

void Unit::followPath() {
	vector3df position = node->getPosition();
	vector3df destination;
	destination.X = path[0].X * 10;
	destination.Z = path[0].Y * 10;

	if(position.getDistanceFrom(destination) < .5f) {
		node->setPosition(destination);
		path.erase(path.begin());
		return;
	}

	destination -= position;
	destination = destination.normalize();
	destination *= WALKSPEED;
	destination *= Game::getInstance().delta;
	position += destination;

	node->setPosition(position);
}

void Unit::attackTarget(Entity* target)
{
	if (target->defense >= attack)
	{
		//attackAnimation
		target->hp--;
	}
	else
	{
		//attackAnimation
		target->hp -= (attack - target->defense);
	}
}

int randSeedCount = 0;
void Unit::addModel() {
	IAnimatedMeshSceneNode* modelNode = Game::getInstance().sceneManager->addAnimatedMeshSceneNode( model, node );
	if (modelNode)
    {
        modelNode->setMaterialFlag(EMF_LIGHTING, false);
        modelNode->setMD2Animation(scene::EMAT_STAND);
		modelNode->setMaterialTexture( 0, Game::getInstance().videoDriver->getTexture("C:/irrlicht-1.8/media/sydney.bmp") );
		modelNode->setID(0);
		modelNode->setScale(vector3df(0.15f, 0.15f, 0.15f) );
		
		srand(time(NULL)+randSeedCount++);
		float randX = rand() % 8 - 4;
		srand(time(NULL)+randSeedCount++);
		float randZ =rand() % 8 - 4;
		modelNode->setPosition(vector3df(randX, 2.5f, randZ));
    }

	modelNodes.push_back(modelNode);
}

void Unit::removeModel() {
	IAnimatedMeshSceneNode* modelNode = modelNodes[modelNodes.size()-1];
	modelNodes.pop_back();
	Game::getInstance().sceneManager->addToDeletionQueue(modelNode);
}