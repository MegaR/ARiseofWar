#include "GameScene.h"
#include "UnitKnight.h"
#include "UnitPeasant.h"

Button* returnToMenuButton;
Button* exitGameButton;
Button* nextTurnButton;

GameScene::GameScene() {
	Game* game = &Game::getInstance();

	game->camera->setPosition( vector3df(0, 35, -40));
	moveCamera(0,0,0);
	players[0] = new Player();
	players[1] = new EnemyPlayer();
	currentPlayer = 0;
	turnCount = 0;
	storedEntity = (Entity*)NULL;
	playerunits = true;
	enemyunits = true;

	
	int sW = game->screenWidth;
	int sH = game->screenHeight;
	int bW = 100, 
		bH = 100;
	int bX, bY;
	bX = sW - bW;
	bY = sH - bH;

	background = game->gui->addImage(rect<s32>(0,0, game->screenWidth, game->screenHeight));
	background->setVisible(false);
	background->setScaleImage(true);
	ITexture* buttonTexture = Game::getInstance().videoDriver->getTexture("res/guiButtonSmall.png");

	returnToMenuButton = new Button(bX-100, bY, bW, bH, "Return\nto Menu", buttonTexture);
	exitGameButton = new Button(bX, bY, bW, bH, "Exit\nGame", buttonTexture);
	nextTurnButton = new Button(bX-200, bY, bW, bH, "Next\nTurn", buttonTexture);

	entities.push_back(new Barracks(3,3,0));
	tilesystem.create(this);
	
	IAnimatedMesh* mesh = game->sceneManager->getMesh("res/tileSelected.3DS");
	selectedNode = game->sceneManager->addMeshSceneNode(mesh);
	selectedNode->setMaterialFlag(EMF_LIGHTING, false);
	selectedNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	selectedNode->setMaterialTexture( 0, game->videoDriver->getTexture("res/tileSelected.png") );
	selectedNode->setPosition(vector3d<f32>(50, 0, 50) );
	selectedNode->setID(0);
}

GameScene::~GameScene() {
	delete players[0];
	delete players[1];
	delete returnToMenuButton;
	delete exitGameButton;
	
	for(int i = 0; i < entities.size(); i++) {
		delete entities.at(i);
	}
	background->setVisible(false);
	selectedNode->remove();
}

void GameScene::update() {
	Game* game = &Game::getInstance();
	updateMouse();
	returnToMenuButton->update();
	exitGameButton->update();
	nextTurnButton->update();
	//left click
	if(game->eventReceiver->isLeftMousePressed()){
		clickEntity();

	}
	//right click
	if(game->eventReceiver->isRightMousePressed()){
		if(storedEntity) {
			actionEntity();
		}
	}

	//Button handlers enzo
	if (returnToMenuButton->pressed == true)
	{
		
		game->changeScene(new MenuScene());
	}

	if (exitGameButton->pressed == true)
	{
		Game::getInstance().device->closeDevice();
		exit (1);
	}

	if (nextTurnButton->pressed == true) {
		nextTurn();
	}

	for(int i = 0; i < entities.size(); i++) {
		entities.at(i)->update();
	}

	if(enemyunits == false){
		background->setImage(game->videoDriver->getTexture("res/guiWin.png"));
		background->setVisible(true);
		nextTurnButton->btn->setVisible(false);
	}

	if(playerunits == false){
		background->setImage(game->videoDriver->getTexture("res/guiLose.png"));
		background->setVisible(true);
		nextTurnButton->btn->setVisible(false);
	}
}

void GameScene::nextTurn() {
	players[currentPlayer]->endTurn();
	playerunits = false;
	enemyunits = false;
	for(int i = 0; i < entities.size(); i++) {
		if(entities[i]->player == currentPlayer) {
			entities[i]->endTurn();
		}
		
		if(entities[i]->player == 1){
			enemyunits = true;
		}

		if(entities[i]->player == 0){
			playerunits = true;
		}
	}

	currentPlayer = currentPlayer == 1 ? 0 : 1;
	players[currentPlayer]->startTurn();
	for(int i = 0; i < entities.size(); i++) {
		if(entities[i]->player == currentPlayer) {
			entities[i]->startTurn();
		}
	}

	if(currentPlayer == 1) {
		((EnemyPlayer*)players[1])->turn();
	}

	turnCount++;
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

	if(x < 10) {
		moveCamera(-CAMERASPEED * game->delta, 0, 0);
	}
	if(x > game->screenWidth-10) {
		moveCamera(CAMERASPEED * game->delta, 0, 0);
	}
	if(y < 10) {
		moveCamera(0,0,CAMERASPEED * game->delta);
	}
	if(y > game->screenHeight-10) {
		moveCamera(0,0,-CAMERASPEED * game->delta);
	}

	int height = -game->eventReceiver->getScroll() * ZOOMSPEED;
	if(height) {
		moveCamera(0, height, 0);
	}

}

void GameScene::moveCamera(float x, float y, float z) {
	ICameraSceneNode* camera = Game::getInstance().camera;
	vector3df position = camera->getPosition();
	position.X += x;
	position.Y += y;
	if(position.Y > CAMERAMAX) position.Y = CAMERAMAX;
	if(position.Y < CAMERAMIN) position.Y = CAMERAMIN;
	position.Z += z;
	camera->setPosition(position);
	position.Y += -1;
	position.Z += 0.5f;
	camera->setTarget(position);
	
}

vector2d<int> GameScene::mouseRay(){
	
	Game* game = &Game::getInstance();
	vector2d<s32> mousePosition = game->device->getCursorControl()->getPosition();
	vector3df posTile;
	position2d<s32> *pos = new position2d<s32>(mousePosition.X,mousePosition.Y);

		//get camera
		ICameraSceneNode* camera = Game::getInstance().camera;
		//create line from scrren coords
		line3d<f32> *line3d_trace = new line3d<f32>;
		*line3d_trace=game->sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(*pos,camera);

		//use line to get scene node
		scene::ISceneNode *nodeline = game->sceneManager->getSceneCollisionManager()->getSceneNodeFromRayBB(*line3d_trace,1,false);
		
		if (nodeline){
			posTile = nodeline->getPosition();
			return vector2d<int>((posTile.X/10), (posTile.Z/10));
			
			// return x, y coords if not empty			
		};
		return vector2d<int>(-1,-1);
}

void GameScene::actionEntity() {
	vector2d<int> hit = mouseRay();
	Entity *ent;

	if(currentPlayer != 0) return;
	if(storedEntity->player != 0) return;

	if(hit == vector2d<int>(-1, -1) ) return;
	ent = getEntity(hit.X, hit.Y);

	if(!ent) {
		((Unit*)storedEntity)->moveTo(hit.X, hit.Y);
		clickEntity();
	}

	if(ent) {
		//attack or somethin
		((Unit*)storedEntity)->attackTarget(ent);
		
	}
}

void GameScene::clickEntity(){
	vector2d<int> hit = mouseRay();
	Entity *ent;

	if(hit == vector2d<int>(-1, -1) ) return;
	
	Building* building = dynamic_cast<Building*>(getEntity(hit.X, hit.Y) );
	if(!building) {
		selectedNode->setPosition(vector3df(hit.X*10,0,hit.Y*10));
		selectedNode->setScale(vector3df(1,1,1));
	} else {
		selectedNode->setScale(vector3df(building->sizeX+0.25, 2.5f, building->sizeY+0.25) );
		selectedNode->setPosition(vector3df(building->tileX*10+(5*(building->sizeX/2)), 0.0f, building->tileY*10+(5*(building->sizeY/2))));
	}
	
	deselectEntity();
	ent = getEntity(hit.X,hit.Y);
	if(ent) {
		selectEntity(ent);
	}
}

void GameScene::deselectEntity(){
	if(storedEntity) {
		storedEntity->deselected();
	}
	storedEntity= (Entity*)NULL;
}

void GameScene::selectEntity(Entity* ent) {
	storedEntity = ent;
	storedEntity->selected();
}


Entity* GameScene::getEntity(int x, int y) {
	for(int i = 0; i < entities.size(); i++) {
		Building* building = dynamic_cast<Building*>(entities[i]);
		if( !building ) {
			if(entities[i]->tileX == x && entities[i]->tileY== y) {
				return entities[i];
			}
		} else { // entity is a building
			if(x >= building->tileX && x < building->tileX + building->sizeX && y >= building->tileY && y < building->tileY + building->sizeY) {
				return entities[i];
			}
		}
	}
	
	return NULL;
}

void GameScene::removeEntity(Entity* ent){
	for(int i = 0; i < entities.size(); i++){
		if(ent == entities[i]){
			if(storedEntity == entities[i]) {
				deselectEntity();
			}
			delete entities[i];
			entities.erase(entities.begin()+i);
			return;
		}
	}
}

std::vector<vector2d<int>>* GameScene::findPath(vector2d<int> start, vector2d<int> end) {
	std::vector<vector2d<int>> closedset;
	std::vector<vector2d<int>> openset;

	vector2d<int> came_from[MAPSIZE][MAPSIZE];
	int g_score[MAPSIZE][MAPSIZE];
	int f_score[MAPSIZE][MAPSIZE];
	
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			g_score[x][y] = INT_MAX;
			f_score[x][y] = INT_MAX;
		}
	}

	openset.push_back(start);
	g_score[start.X][start.Y] = 0;
	f_score[start.X][start.Y] = g_score[start.X][start.Y] + heuristic_cost_estimate(start, end);

	while (!openset.empty()) {
		vector2d<int> current;

		//current == lowest f_score in openlist
		int lowest = INT_MAX;
		for(int i = 0; i < openset.size(); i++) {
			if(lowest > f_score[openset.at(i).X][openset.at(i).Y]) {
				lowest = f_score[openset.at(i).X][openset.at(i).Y];
				current = openset.at(i);
			}
		}

		if (current == end) {
			return reconstructed_path(came_from, end, start);
		}
		
		int index = findElement(openset, current);
		openset.erase(openset.begin()+index);
		closedset.push_back(current);

		std::vector<vector2d<int>>* neighbors = get_neighbors(current);
		for(int i = 0; i < neighbors->size(); i++) {
			int tentative_g_score = g_score[current.X][current.Y] + current.getDistanceFrom(neighbors->at(i));
			int tentative_f_score = tentative_g_score; + heuristic_cost_estimate(neighbors->at(i), end);

			if ( findElement(closedset, neighbors->at(i)) >= 0 &&
				tentative_f_score >= f_score[neighbors->at(i).X][neighbors->at(i).Y]) {
				continue;
			}

			if (findElement(openset, neighbors->at(i)) == -1 || 
				tentative_f_score < f_score[neighbors->at(i).X][neighbors->at(i).Y] ) {
					came_from[neighbors->at(i).X][neighbors->at(i).Y] = current;
					g_score[neighbors->at(i).X][neighbors->at(i).Y] = tentative_g_score;
					f_score[neighbors->at(i).X][neighbors->at(i).Y] = tentative_f_score;
					if ( findElement(openset, neighbors->at(i) ) == -1) {
						openset.push_back(neighbors->at(i) );
					}
			}

		}
		delete neighbors;

	}

	return NULL;
}



int GameScene::findElement(std::vector<vector2d<int>> list, vector2d<int> element) {
	for(int i = 0; i < list.size(); i++) {
		if(list.at(i) == element) {
			return i;
		}
	}
	return -1;
}

vector2d<int> GameScene::lowest(int list[][MAPSIZE]) {
	int lowest = list[0][0];
	vector2d<int> lowestLocation(0,0);

	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			if(list[x][y] < lowest) {
				lowest = list[x][y];
				lowestLocation.X = x;
				lowestLocation.Y = y;
			}
		}
	}

	return lowestLocation;
}

std::vector<vector2d<int>>* GameScene::get_neighbors(vector2d<int> current) {
	std::vector<vector2d<int>> *list = new std::vector<vector2d<int>>();

	if(current.X > 0) {
		if(!getEntity(current.X-1, current.Y) ) {
			if(tilesystem.tiles[current.X-1][current.Y]->walkable) {
				list->push_back(vector2d<int>(current.X-1, current.Y));
			}
		}
	}

	if(current.X < MAPSIZE-1) {
		if(!getEntity(current.X+1, current.Y) ) {
			if(tilesystem.tiles[current.X+1][current.Y]->walkable) {
				list->push_back(vector2d<int>(current.X+1, current.Y));
			}
		}
	}

	if(current.Y > 0) {
		if(!getEntity(current.X, current.Y-1) ) {
			if(tilesystem.tiles[current.X][current.Y-1]->walkable) {
				list->push_back(vector2d<int>(current.X, current.Y-1));
			}
		}
	}
	if(current.Y < MAPSIZE-1) {
		if(!getEntity(current.X, current.Y+1) ) {
			if(tilesystem.tiles[current.X][current.Y+1]->walkable) {
				list->push_back(vector2d<int>(current.X, current.Y+1));
			}
		}
	}

	return list;
}

int GameScene::heuristic_cost_estimate(vector2d<int> current, vector2d<int> goal) {
	vector2d<int> retval = goal - current;
	return goal.getDistanceFromSQ(current);
}

std::vector<vector2d<int>>* GameScene::reconstructed_path(
	vector2d<int> came_from[][MAPSIZE],
	vector2d<int> end,
	vector2d<int> start) {

	std::vector<vector2d<int>>* list = new std::vector<vector2d<int>>();

	vector2d<int> current(end.X, end.Y);
	while(current != start) {
		list->push_back(current);
		current = came_from[current.X][current.Y];
	}

	return list;
}