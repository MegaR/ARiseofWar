#include "TileSystem.h"


TileSystem::TileSystem(void)
{
	cout << "Filling tilemap" << endl;
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			tiles[x][y] = new TileGrass(x,y);
		}
	}

	findPath(vector2d<int>(0,0), vector2d<int>(10,5) );
}

TileSystem::~TileSystem(void)
{
	for(int x = 0; x < MAPSIZE; x++) {
		for(int y = 0; y < MAPSIZE; y++) {
			delete tiles[x][y];
		}
	}
}

std::vector<vector2d<int>>* TileSystem::findPath(vector2d<int> start, vector2d<int> end) {
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



int TileSystem::findElement(std::vector<vector2d<int>> list, vector2d<int> element) {
	for(int i = 0; i < list.size(); i++) {
		if(list.at(i) == element) {
			return i;
		}
	}
	return -1;
}

vector2d<int> TileSystem::lowest(int list[][MAPSIZE]) {
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

std::vector<vector2d<int>>* TileSystem::get_neighbors(vector2d<int> current) {
	std::vector<vector2d<int>> *list = new std::vector<vector2d<int>>();

	if(current.X > 0) {
		list->push_back(vector2d<int>(current.X-1, current.Y));
		/*if(current.Y > 0) {
			list->push_back(vector2d<int>(current.X-1, current.Y-1));
		}
		if(current.Y < MAPSIZE) {
			list->push_back(vector2d<int>(current.X-1, current.Y+1));
		}*/
	}

	if(current.X < MAPSIZE) {
		list->push_back(vector2d<int>(current.X+1, current.Y));
		/*if(current.Y > 0) {
			list->push_back(vector2d<int>(current.X+1, current.Y-1));
		}
		if(current.Y < MAPSIZE) {
			list->push_back(vector2d<int>(current.X+1, current.Y+1));
		}*/
	}

	if(current.Y > 0) {
		list->push_back(vector2d<int>(current.X, current.Y-1));
	}
	if(current.Y < MAPSIZE) {
		list->push_back(vector2d<int>(current.X, current.Y+1));
	}

	return list;
}

int TileSystem::heuristic_cost_estimate(vector2d<int> current, vector2d<int> goal) {
	vector2d<int> retval = goal - current;
	return goal.getDistanceFromSQ(current);
}

std::vector<vector2d<int>>* TileSystem::reconstructed_path(
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