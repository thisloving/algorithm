#ifndef _A_STAR_H_
#define _A_STAR_H_

#include <vector>
#include <list>

const static int kCost1st = 10;
const static int kCost2nd = 14;

class Point {
public:
	Point() : 
	F(0), G(0), H(0),
	parent(nullptr),
	x(0), y(0)
	{}

	Point(int _x, int _y) :
	F(0), G(0), H(0),
	parent(nullptr),
	x(_x), y(_y)
	{}


	int F, G, H;
	Point* parent;
	int x, y;
};

class AStar {
public:
	AStar(); 

public:	
	void   Initilize(std::vector<std::vector<int> >& _maze);
	Point* FindPath(Point* startPoint, Point* endPoint, bool isIgnoreCorner);
	void   PrintPath(Point* point);
	std::list<Point*> GetPath(Point* startPoint, Point* endPoint, bool
	isIgnoreCorner);

private:
	int  calcG(Point* curPoint, Point* surroundPoint);
	int  calcH(Point* surroundPoint, Point* endPoint);
	int  calcF(Point* surroundPoint);
	
	Point* getLeastFInOpenList();
	std::vector<Point*>   getSurroundPoints(const Point* curPoint, bool
	isIgnoreCorner) const;
	Point* isInList(const std::list<Point*>& container,  const Point* surroundPoint) const;
	bool   isCanReach(const Point* point, const Point* surroundPoint, bool
	isIgnoreCorner) const; 

private:
	std::vector<std::vector<int> > maze;
	
	// The priority_queue cannot be traversed
	std::list<Point*> openList;
	std::list<Point*> closeList;
};

#endif
