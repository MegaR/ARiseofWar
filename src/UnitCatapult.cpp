#include "UnitCatapult.h"

#include "Game.h"

#include <iostream>
using namespace std;

UnitCatapult::UnitCatapult(int _x, int _y, int _player, Scene* scene)  : Unit(_x, _y, _player, scene)
{	
	maxHP = 8;
	hp = maxHP;
	attack = 9;
	defense = 1;
	maxDistance = 3;
	attackDistance = 2;
	maxModels = 1;

	
	Game* game = &Game::getInstance();
	model = game->sceneManager->getMesh("res/unitCatapult.md2");
	
	if(player == 0) {
		texture = game->videoDriver->getTexture("res/unitCatapult.png");
	} else {
		texture = game->videoDriver->getTexture("res/unitCatapultEnemy.png");
	}
	
	for(int i = 0; i < maxModels; i++) {
		addModel();
	}
}

void UnitCatapult::addModel(){
	IAnimatedMeshSceneNode* modelNode = Game::getInstance().sceneManager->addAnimatedMeshSceneNode( model, node );
	if (modelNode)
    {
		modelNode->setMaterialTexture( 0, texture );
		modelNode->getMaterial(0).Shininess = 0;
		modelNode->setScale(vector3df(0.75f, 0.75f, 0.75f) );
		
		modelNode->addShadowVolumeSceneNode(0, 0, false);
		modelNode->setID(0);

		currentAnimation = IDLE_ANIMATION;
		cout << "add model cata" << endl; 
		modelNode->setPosition(vector3df(0, 0.0f, 0));
    }

	modelNodes.push_back(modelNode);
}


UnitCatapult::~UnitCatapult(void)
{
}

void UnitCatapult::updateAnimations() {
	switch(currentAnimation)
	{
		case IDLE_ANIMATION:
			if(hasAttacked) { currentAnimation = ATTACKING_ANIMATION; break; }
			if (!isAnimating[currentAnimation])
			{
				for (int i = 0; i < modelNodes.size(); i++) 
				{
					modelNodes[i]->setFrameLoop(0, 0);
					modelNodes[i]->setAnimationSpeed(0);
				}
			
				isAnimating[IDLE_ANIMATION] = true;
				isAnimating[WALKING_ANIMATION] = false;
				isAnimating[ATTACKING_ANIMATION] = false;
				isAnimating[DEATH_ANIMATION] = false;
				cout << "Turned on Idle Animation" << endl;
			}
			break;

		case WALKING_ANIMATION:
			if (!isAnimating[currentAnimation])
			{
				for (int i = 0; i < modelNodes.size(); i++) 
				{
					modelNodes[i]->setFrameLoop(0, 40);
					modelNodes[i]->setCurrentFrame(0);
					modelNodes[i]->setAnimationSpeed(60);
				}
			
				isAnimating[IDLE_ANIMATION] = false;
				isAnimating[WALKING_ANIMATION] = true;
				isAnimating[ATTACKING_ANIMATION] = false;
				isAnimating[DEATH_ANIMATION] = false;
				cout << "Turned on Walking Animation" << endl;
			}
			break;

		case ATTACKING_ANIMATION:
			if (!isAnimating[currentAnimation])
			{
				for (int i = 0; i < modelNodes.size(); i++) 
				{
					modelNodes[i]->setFrameLoop(40, 70);
					modelNodes[i]->setCurrentFrame(40);
					modelNodes[i]->setAnimationSpeed(15);
				}
			
				isAnimating[IDLE_ANIMATION] = false;
				isAnimating[WALKING_ANIMATION] = false;
				isAnimating[ATTACKING_ANIMATION] = true;
				isAnimating[DEATH_ANIMATION] = false;
				cout << "Turned on Attacking Animation" << endl;
			}

			int currentAnimationFrame;
			for (int i = 0; i < modelNodes.size(); i++) 
			{
				currentAnimationFrame = modelNodes[i]->getFrameNr();
				if (currentAnimationFrame > 65) currentAnimation = IDLE_ANIMATION;
			}
			break;

		default:{ 
			cout << "Unknown animation ID!" << endl;
		}break;
	}
}