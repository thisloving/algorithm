#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

const static int kVertexNum = 7;

struct Edge {
	Edge(): src(0), dst(0), weight(0) 
	{}

	int src, dst, weight;
};

struct cmp {
	bool operator() (const Edge& a, const Edge& b) const {
		return a.weight > b.weight;
	}
};

class Graph {
public:
	Graph()
	{}

public:
	void  AddEdge(int src, int dst, int weight);
	void  Initialize();
	void  Prim(int start);

private:
	std::map<int, std::vector<struct Edge> > vertexs;
	std::priority_queue<struct Edge, std::vector<struct Edge>, cmp> p;

	int distance[kVertexNum];
	std::map<int, struct Edge> path;
};

void Graph::AddEdge(int src, int dst, int weight) {
	{
		Edge e;
		e.src = src;
		e.dst = dst;
		e.weight = weight;
		vertexs[e.src].push_back(e);
	}

	{
		Edge e;
		e.src = dst;
		e.dst = src;
		e.weight = weight;
		vertexs[e.src].push_back(e);
	}
}

void Graph::Initialize() {
	AddEdge(0, 1, 1);
	AddEdge(1, 2, 2);
	AddEdge(2, 3, 3);
	AddEdge(3, 4, 4);
	AddEdge(4, 5, 5);
	AddEdge(5, 6, 6);
	AddEdge(6, 4, 7);
	AddEdge(6, 3, 8);
	AddEdge(5, 3, 9);
	AddEdge(3, 1, 10);
	AddEdge(2, 0, 11);
	AddEdge(3, 0, 12);

	for (int i = 0; i < kVertexNum; i++) {
		distance[i] = INT_MAX;
	}
}

void Graph::Prim(int start) {
	struct Edge e;
	e.src    = start;
	e.dst    = start;
	e.weight = 0;

	this->p.push(e);
	this->distance[start] = 0;

	while(!p.empty()) {
		struct Edge v = this->p.top();
		this->p.pop();

		std::map<int, struct Edge>::iterator iter = this->path.find(v.dst);
		if (iter != this->path.end()) {
			continue;
		}
		
		this->path[v.dst] = v;

		while (!p.empty()) {
			this->p.pop();
		}
	
		int weight = 0;
		iter = this->path.begin();
		for (; iter != this->path.end(); ++iter) {
			std::map<int, std::vector<struct Edge> >::iterator iter1st =
			vertexs.find(iter->first);
			if (iter1st == vertexs.end()) {
				continue;
			}

			std::vector<struct Edge>::iterator iter2nd = iter1st->second.begin();
			for (; iter2nd != iter1st->second.end(); ++iter2nd) {
				if (this->path.find(iter2nd->dst) != this->path.end()) {
					continue;
				}

				struct Edge n;
				n.src    = iter2nd->src;
				n.dst    = iter2nd->dst;
				n.weight = iter2nd->weight;
				this->p.push(n);
			}
		}
	}

	std::map<int, struct Edge>::iterator iter = this->path.begin();
	for (; iter != this->path.end(); ++iter) {
		if (iter->second.dst == iter->second.src) {
			continue;
		}

		cout << "dst:" << iter->first << " src:" << iter->second.src << " weight:" << iter->second.weight << endl;
	}
}

int main()
{
	Graph graph;
	graph.Initialize();

	graph.Prim(6);
}
