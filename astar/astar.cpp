#include "astar.h"
#include <iostream>
#include <cmath>

AStar::AStar() {
}

void AStar::Initilize(std::vector<std::vector<int> >& _maze) {
	this->maze = _maze;
	this->openList.clear();
}

int AStar::calcG(Point* curPoint, Point* surroundPoint) {
	int extra_g = (abs(surroundPoint->x-curPoint->x) +
	abs(surroundPoint->y-curPoint->y)) == 1 ? kCost1st : kCost2nd; 
	int parent_g = curPoint->G;
	return extra_g + parent_g;
}

int AStar::calcH(Point* surroundPoint, Point* endPoint) {
	return sqrt((surroundPoint->x-endPoint->x)*(surroundPoint->x-endPoint->x) +
	(surroundPoint->y-endPoint->y)*(surroundPoint->y-endPoint->y)) * kCost1st;		
}

int AStar::calcF(Point* surroundPoint) {
	return surroundPoint->G + surroundPoint->H;
}

Point* AStar::getLeastFInOpenList() {
	if (!openList.empty()) {
		auto resPoint = openList.front();
		for (auto& i : this->openList) {
			if (i->F < resPoint->F) {
				resPoint = i;
			}
		}

		return resPoint;
	}

	return nullptr;
}

std::vector<Point*> AStar::getSurroundPoints(const Point* curPoint, bool
isIgnoreCorner) const {
	std::vector<Point*> surroundPoints;
		
	for (int i = curPoint->x-1; i <= curPoint->x+1; i++) {
		for (int j = curPoint->y-1; j <= curPoint->y+1; j++) {
			if (!isCanReach(curPoint, new Point(i, j), isIgnoreCorner)) {
				continue;
			}
			surroundPoints.push_back(new Point(i, j));
		}
	}

	return surroundPoints;
}

bool AStar::isCanReach(const Point* point, const Point* surroundPoint, bool
isIgnoreCorner) const {
	if (surroundPoint->x < 0 || surroundPoint->x > maze.size()-1 ||
		surroundPoint->y < 0 || surroundPoint->y > maze[0].size()-1 ||
		isInList(this->closeList, surroundPoint) != nullptr ||
		maze[surroundPoint->x][surroundPoint->y] == 1 || 
		(point->x == surroundPoint->x && point->y == surroundPoint->y)) {
	} else {
		if (abs(point->x-surroundPoint->x) + abs(point->y-surroundPoint->y) == 1) {
			return true;
		} else {
			if (maze[point->x][surroundPoint->y] == 0 &&
				maze[surroundPoint->x][point->y] == 0) {
				return true;
			} else {
				return isIgnoreCorner;
			}
		} 
	}
	return false;
}

Point* AStar::isInList(const std::list<Point*>& container, const Point* point) const {
	for (auto i : container) {
		if (i->x == point->x && i->y == point->y) {
			return i;
		}
	}
	return nullptr;
}

Point* AStar::FindPath(Point* startPoint, Point* endPoint, bool isIgnoreCorner) {	
	this->openList.push_back(startPoint);

	Point *curPoint = nullptr;
	std::vector<Point*> surroundPoints;
	while(!this->openList.empty()) {
		curPoint = this->getLeastFInOpenList();
		this->openList.remove(curPoint);
		this->closeList.push_back(curPoint);
		
		surroundPoints = this->getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto& surroundPoint : surroundPoints) {
			if (!isInList(openList, surroundPoint)){
				surroundPoint->parent = curPoint;
 				surroundPoint->G = this->calcG(curPoint, surroundPoint);
				surroundPoint->H = this->calcH(surroundPoint, endPoint);
				surroundPoint->F = this->calcF(surroundPoint);

				this->openList.push_back(surroundPoint);
			} else {
				int temp_g = this->calcG(curPoint, surroundPoint);
				if (temp_g < surroundPoint->G) {
					surroundPoint->parent = curPoint;
					surroundPoint->G = temp_g;
					surroundPoint->F = this->calcF(surroundPoint);
				}
			}
		}

		Point* res_point = isInList(this->closeList, endPoint);
		if (res_point != nullptr) {
			return res_point;
		}
	}

	return nullptr;
}

std::list<Point*> AStar::GetPath(Point* startPoint, Point* endPoint, bool
isIgnoreCorner) {
	Point* result = FindPath(startPoint, endPoint, isIgnoreCorner);
	std::list<Point*> path;
	while (result) {
		path.push_front(result);
		result = result->parent;
	}

	std::cout << "openList: " << std::endl;
	for (auto& i : openList) {
		std::cout << "(" << i->x << "," << i->y << ")" << std::endl;	
	}

	std::cout << "closeList:" << std::endl;
	for (auto& i : closeList) {
		std::cout << "(" << i->x << "," << i->y << ")" << std::endl;
	}

	openList.clear();
	closeList.clear();

	return path;
}

void AStar::PrintPath(Point* point) {
	if (point == nullptr) {
		return;
	}

	while(point) {
		std::cout << "(" << point->x << " ," << point->y << ")" << std::endl;
		point = point->parent;
	}
}
