#include "Unit.h"

#include "Game.h"
#include <iostream>
using namespace std;

ISoundEngine* uBGM;

Unit::Unit(int tileX, int tileY, int player, Scene* scene) : Entity(scene)
{
	((GameScene*)scene)->tilesystem.tiles[tileX][tileY]->setEntity(this);
	this->tileX = tileX;
	this->tileY = tileY;
	this->player = player;
	hasAttacked = false;
	hasMoved = false;

	moveAnimator = NULL;
	currentAnimation = IDLE_ANIMATION;

	isAnimating[IDLE_ANIMATION] = false;
	isAnimating[WALKING_ANIMATION] = false;
	isAnimating[ATTACKING_ANIMATION] = false;
	isAnimating[DEATH_ANIMATION] = false;

	node = Game::getInstance().sceneManager->addEmptySceneNode(0, 0);
	node->setPosition(vector3df(tileX * 10, 0, tileY * 10) );

	uBGM = createIrrKlangDevice();
}

Unit::~Unit()
{
	cout << "destroying Unit" << endl;

	while(modelNodes.size() > 0) {
		removeModel();
	}
	
	if(((GameScene*)Game::getInstance().currentScene)->tilesystem.tiles[tileX][tileY]->getEntity() == this) {
		((GameScene*)Game::getInstance().currentScene)->tilesystem.tiles[tileX][tileY]->setEntity(NULL);
	}
	//uBGM->drop(); // sorry for the memory leaks
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
					modelNodes[i]->setCurrentFrame(rand() % (183 - 105) + 105);
					modelNodes[i]->setAnimationSpeed(60);
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
					modelNodes[i]->setCurrentFrame(rand() % 25 +53);
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
		if(!hasMoved) {
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

	if(!scene->tilesystem.tiles[x][y]->walkable) {
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
		IAnimatedMesh* model = game->sceneManager->getMesh("res/tileDistance.3ds");
		ISceneNode* node = game->sceneManager->addMeshSceneNode(model);
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		if(inAttackRange) {
			node->setMaterialTexture( 0, game->videoDriver->getTexture("res/tileDistanceRed.png") );
		} else {
			node->setMaterialTexture( 0, game->videoDriver->getTexture("res/tileDistanceBlue.png") );
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

	
	((GameScene*)scene)->tilesystem.tiles[tileX][tileY]->setEntity(NULL);
	tileX = path[path.size()-1].X;
	tileY = path[path.size()-1].Y;
	((GameScene*)scene)->tilesystem.tiles[tileX][tileY]->setEntity(this);
	hasMoved = true;
}

void Unit::followPath() 
{
	if(moveAnimator && !moveAnimator->hasFinished()) {
		return;
	}

	if(moveAnimator) {
		node->removeAnimators();
		delete moveAnimator;
	}

	if(path.size() == 0) return;

	Game* game = &Game::getInstance();
	vector3df destination;
	destination.X = path[0].X * 10;
	destination.Z = path[0].Y * 10;

	vector3df targetRotation;
	float cos = (destination-node->getPosition()).dotProduct(vector3df(100,0,0)) / ((destination-node->getPosition()).getLength() * vector3df(100,0,0).getLength());
	float angle = (acos(cos) / PI) * 180;
	if(destination.Z < node->getPosition().Z) angle = -angle;
	targetRotation.Y = -angle + 270;
	for(int i = 0; i < modelNodes.size(); i++) {
		modelNodes[i]->setRotation(targetRotation);
	}

	moveAnimator = game->sceneManager->createFlyStraightAnimator(node->getPosition(), destination, WALKSPEED);
	node->addAnimator(moveAnimator);

	path.erase(path.begin());
}

float Unit::getAngleBetween (const vector3df& vec1, const vector3df& vec2)
{
   const float dotProduct = vec1.X * vec2.X + vec1.Y * vec2.Y + vec1.Z * vec2.Z;
   const float length1 = sqrt (vec1.X * vec1.X + vec1.Y * vec1.Y + vec1.Z * vec1.Z);
   const float length2 = sqrt (vec2.X * vec2.X + vec2.Y * vec2.Y + vec2.Z * vec2.Z);
   
   const float cosAngle = dotProduct / (length1 * length2);
   return acos (cosAngle);
}

void Unit::attackTarget(Entity* target)
{
	if(player == target->player) { return; }
	if(hasAttacked == true) { return; }
	if(!target->inAttackRange(tileX, tileY, attackDistance)) { return; }

	int damage = attack - target->defense;
	if(damage > 0) {
		target->handleDamage(damage);
	}

	currentAnimation = ATTACKING_ANIMATION;
	hasAttacked = true;
}

void Unit::updateModels() {
	while (modelNodes.size() > hp / (maxHP / maxModels) && modelNodes.size() > 1) {
		removeModel();
	}
	while (modelNodes.size() < hp / (maxHP / maxModels) ) {
		addModel();
	}
}

void Unit::addModel() {
	IAnimatedMeshSceneNode* modelNode = Game::getInstance().sceneManager->addAnimatedMeshSceneNode( model, node );
	if (modelNode)
    {
		modelNode->setMaterialTexture( 0, texture );
		modelNode->getMaterial(0).Shininess = 0;
		modelNode->setScale(vector3df(0.15f, 0.15f, 0.15f) );
		modelNode->addShadowVolumeSceneNode(0, 0, false);
		modelNode->setID(0);

		currentAnimation = IDLE_ANIMATION;
		
		float randX = rand() % 8 - 4;
		float randZ =rand() % 8 - 4;
		modelNode->setPosition(vector3df(randX, 0.0f, randZ));
    }

	modelNodes.push_back(modelNode);
}

void Unit::removeModel() {
	if(modelNodes.size() < 1) return;
	IAnimatedMeshSceneNode* modelNode = modelNodes[modelNodes.size()-1];
	modelNodes.pop_back();
	modelNode->remove();
}

void Unit::startTurn() {
	hasAttacked = false;
	hasMoved = false;
}

void Unit::endTurn() {

}

bool Unit::handleDamage(int damage){
	if(Entity::handleDamage(damage)) {
		updateModels();
		return true;
	}
	return false;
}

bool Unit::enemyTurn() {
	vector<Entity*>* targets = findTargets();
	
	for(int i = 0; i < targets->size(); i++) {
		if( attemptTarget(targets->at(i) ) ) {
			cameraFocus();
			delete targets;
			return false;
		}
	}

	cout << "turn failed!" << endl;
	delete targets;
	return false;
}

bool Unit::attemptTarget(Entity* target) {
	cout << "attemptTarget" << endl;
	if(!hasAttacked && 
		target->inAttackRange(tileX, tileY, attackDistance) ) {
		attackTarget(target);
		cout << "attacked" << endl;
		return true;
	}


	if(!hasMoved) {
		vector2d<int> destination = availableTile(target);
		if(destination != vector2d<int>(-1, -1) ) {
			moveTo(destination.X, destination.Y);
			if(!hasMoved) return false;
			attemptTarget(target);
			return true;
		} else {
			cout << "no route!?" << endl;
		}
	}

	if(hasMoved && hasAttacked) {
		return true;
	}

	return false;
}

vector2d<int> Unit::availableTile(Entity* target) {
	GameScene* scene = (GameScene*) (Game::getInstance().currentScene);
	vector2d<int> tile(-1, -1);
	vector<vector2d<int>>* candidates;

	candidates = target->getSurroundingTiles();
	for(int i = 0; i < candidates->size(); i++) {
		if(scene->getEntity(candidates->at(i).X, candidates->at(i).Y) ) {
			candidates->erase(candidates->begin() + i);
			i--;
		}		
	}
	
	float lowest = FLT_MAX;
	for(int i = 0; i < candidates->size(); i++) {
		float distance = candidates->at(i).getDistanceFrom(vector2d<int>(tileX, tileY) );
		if(distance < lowest ) {
			tile = candidates->at(i);
			lowest = distance;
		}
	}

	delete candidates;
	return tile;
}

vector<Entity*>* Unit::findTargets() {
	GameScene* scene = (GameScene*) (Game::getInstance().currentScene);
	
	vector<Entity*>* targets = new vector<Entity*>();
	
	for(int i = 0; i < scene->entities.size(); i++) {
		if(scene->entities[i]->player == 1) continue;
		
		bool inserted = false;
		for(int ii = 0; ii < targets->size(); ii++) {
			if( targets->at(ii)->distance(this) > scene->entities[i]->distance(this) ) {
				targets->insert(targets->begin()+ii, scene->entities[i]);
				inserted = true;
				break;
			}
		}

		if(!inserted) {
			targets->push_back(scene->entities[i]);
		}
	}

	return targets;
}