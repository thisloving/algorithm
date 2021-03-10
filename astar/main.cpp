#include "astar.h"
#include <iostream>

int main()
{
	std::vector<std::vector<int> > maze = 
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
		{1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	AStar astar;
	astar.Initilize(maze);

	Point start_point(1, 1);
	Point end_point(6, 10);
	std::list<Point*> path = astar.GetPath(&start_point, &end_point, false);
	
	std::cout << "-----------------------" << std::endl;
	std::cout << "path:" << std::endl;
	for (auto& p : path) {	
		std::cout << "(" << p->x << "," << p->y  << ")" << std::endl;
	}

	return 0;
}
