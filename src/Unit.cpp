#include "Unit.h"

#include "Game.h"
#include <iostream>
using namespace std;

Unit::Unit(int tileX, int tileY, int player)
{
	this->tileX = tileX;
	this->tileY = tileY;
	this->player = player;
	hasAttacked = false;
	hasMoved = false;

	currentAnimation = IDLE_ANIMATION;

	isAnimating[IDLE_ANIMATION] = false;
	isAnimating[WALKING_ANIMATION] = false;
	isAnimating[ATTACKING_ANIMATION] = false;
	isAnimating[DEATH_ANIMATION] = false;

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

void Unit::update() 
{
	updateAnimations();

	if(path.size() > 0) 
	{
		followPath();
		currentAnimation = WALKING_ANIMATION;
	}
	else 
	{
		if (currentAnimation == WALKING_ANIMATION) currentAnimation = IDLE_ANIMATION;
	}
}

void Unit::updateAnimations()
{
	switch(currentAnimation)
	{
		case IDLE_ANIMATION:{
			if (!isAnimating[currentAnimation])
			{
				for (int i = 0; i < modelNodes.size(); i++) 
				{
					modelNodes[i]->setFrameLoop(0, 52);
					modelNodes[i]->setAnimationSpeed(15);
				}
			
				isAnimating[IDLE_ANIMATION] = true;
				isAnimating[WALKING_ANIMATION] = false;
				isAnimating[ATTACKING_ANIMATION] = false;
				isAnimating[DEATH_ANIMATION] = false;
				//cout << "Turned on Idle Animation" << endl;
			}
		}break;

		case WALKING_ANIMATION:{
			if (!isAnimating[currentAnimation])
			{
				for (int i = 0; i < modelNodes.size(); i++) 
				{
					modelNodes[i]->setFrameLoop(105, 183);
					modelNodes[i]->setAnimationSpeed(30);
				}
			
				isAnimating[IDLE_ANIMATION] = false;
				isAnimating[WALKING_ANIMATION] = true;
				isAnimating[ATTACKING_ANIMATION] = false;
				isAnimating[DEATH_ANIMATION] = false;
				//cout << "Turned on Walking Animation" << endl;
			}
		}break;

		case ATTACKING_ANIMATION:{
			if (!isAnimating[currentAnimation])
			{
				for (int i = 0; i < modelNodes.size(); i++) 
				{
					modelNodes[i]->setFrameLoop(53, 104);
					modelNodes[i]->setAnimationSpeed(30);
				}
			
				isAnimating[IDLE_ANIMATION] = false;
				isAnimating[WALKING_ANIMATION] = false;
				isAnimating[ATTACKING_ANIMATION] = true;
				isAnimating[DEATH_ANIMATION] = false;
				//cout << "Turned on Attacking Animation" << endl;
			}

			int currentAnimationFrame;
			for (int i = 0; i < modelNodes.size(); i++) 
			{
				currentAnimationFrame = modelNodes[i]->getFrameNr();
				if (currentAnimationFrame == 103) currentAnimation = IDLE_ANIMATION;
			}
		}break;

		case DEATH_ANIMATION:{
			cout << "Please purchase the premium version for the death animation!" << endl;
			/*if (!isAnimating[currentAnimation])
			{
				for (int i = 0; i < modelNodes.size(); i++) 
				{
					modelNodes[i]->setFrameLoop(184, );
					modelNodes[i]->setAnimationSpeed(25);
				}
			
				isAnimating[IDLE_ANIMATION] = false;
				isAnimating[WALKING_ANIMATION] = false;
				isAnimating[ATTACKING_ANIMATION] = false;
				isAnimating[DEATH_ANIMATION] = true;
			}

			int currentAnimationFrame;
			for (int i = 0; i < modelNodes.size(); i++) 
			{
				currentAnimationFrame = modelNodes[i]->getFrameNr();
				if (currentAnimationFrame == ) currentAnimation = IDLE_ANIMATION;
			}*/
		}break;

		default:{ 
			cout << "Unknown animation ID!" << endl;
		}break;
	}
}

void Unit::selected() {
	
	if(player == 0) {
		if(!hasMoved && !hasAttacked) {
			addDistanceTiles(tileX, tileY, maxDistance);
		}
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

	if(!inAttackRange && hasMoved) return;

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
	if(hasMoved) return;
	if(desX == tileX && desY == tileY) return;

	GameScene* scene = (GameScene*)Game::getInstance().currentScene;
	vector<vector2d<int>>* newPath = scene->findPath(vector2d<s32>(tileX, tileY), vector2d<s32>(desX, desY) );
	if(!newPath) return;
	while(newPath->size() > maxDistance) {
		newPath->erase(newPath->begin());
	}

	while(newPath->size() > 0) {
		path.push_back( newPath->at(newPath->size()-1) );
		newPath->pop_back();
	}
	delete newPath;

	tileX = desX;
	tileY = desY;
	hasMoved = true;
}

void Unit::followPath() {
	vector3df position = node->getPosition();
	vector3df destination;
	vector3df targetRotation;
	destination.X = path[0].X * 10;
	destination.Z = path[0].Y * 10;

	if(position.getDistanceFrom(destination) < .5f) {
		if(path.size() == 1) {
			node->setPosition(destination);
		}
		path.erase(path.begin());
		return;
	}

	destination -= position;
	destination = destination.normalize();
	destination *= WALKSPEED;
	destination *= Game::getInstance().delta;
	if(destination.getLength() > 5) {
		destination.setLength(5);
	}

	//overshoot fix
	if(position.X < path[0].X * 10 && 
		position.X + destination.X > path[0].X * 10) {
			position.X = path[0].X*10;
	}
	if(position.X > path[0].X * 10 && 
		position.X + destination.X < path[0].X * 10) {
			position.X = path[0].X*10;
	}

	if(position.Z < path[0].Y * 10 && 
		position.Z + destination.Z > path[0].Y * 10) {
			position.Z = path[0].Y*10;
	}
	if(position.Z > path[0].Y * 10 && 
		position.Z + destination.Z < path[0].Y * 10) {
			position.Z = path[0].Y*10;
	}

	if (position.X > (position.X+destination.X)) targetRotation.Y = 90.0; //Left
	if (position.X < (position.X+destination.X)) targetRotation.Y = 270.0; //Right
	if (position.Z < (position.Z+destination.Z)) targetRotation.Y = 180.0; //Up
	if (position.Z > (position.Z+destination.Z)) targetRotation.Y = 360.0; //Down

	position += destination;
	
	node->setRotation(targetRotation);
	node->setPosition(position);
}

void Unit::attackTarget(Entity* target)
{
	if(player == target->player) { return; }
	if(hasAttacked == true) { return; }
	if(!target->inAttackRange(tileX, tileY, attackDistance)) { return; }

	int damage = attack - target->defense;
	target->handleDamage(damage);

	currentAnimation = ATTACKING_ANIMATION;
	hasAttacked = true;
}

int randSeedCount = 0;
void Unit::addModel() {
	IAnimatedMeshSceneNode* modelNode = Game::getInstance().sceneManager->addAnimatedMeshSceneNode( model, node );
	if (modelNode)
    {
        modelNode->setMaterialFlag(EMF_LIGHTING, false);
        //modelNode->setMD2Animation(scene::EMAT_STAND);
		modelNode->setMaterialTexture( 0, texture );
		modelNode->setID(0);
		modelNode->setScale(vector3df(0.15f, 0.15f, 0.15f) );

		currentAnimation = IDLE_ANIMATION;
		
		srand(time(NULL)+randSeedCount++);
		float randX = rand() % 8 - 4;
		srand(time(NULL)+randSeedCount++);
		float randZ =rand() % 8 - 4;
		modelNode->setPosition(vector3df(randX, 0.0f, randZ));
    }

	modelNodes.push_back(modelNode);
}

void Unit::removeModel() {
	if(modelNodes.size() < 1) return;
	IAnimatedMeshSceneNode* modelNode = modelNodes[modelNodes.size()-1];
	modelNodes.pop_back();
	//Game::getInstance().sceneManager->addToDeletionQueue(modelNode);
	modelNode->remove();
}

void Unit::startTurn() {
	cout << "start unit" << endl;
	hasAttacked = false;
	hasMoved = false;
}

void Unit::endTurn() {

}

void Unit::handleDamage(int damage){
	Entity::handleDamage(damage);
	for(int i = 0; i < damage; i++){
		removeModel();
	}
}