#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

const static int kVertexNum = 7;

struct Edge {
	Edge() : src(0), dst(0), weight(0)
	{}

	friend bool operator< (const Edge& a, const Edge& b) {
		return a.weight < b.weight;
	}

	int src;
	int dst;
	int weight;
};

struct cmp {
	bool operator()(struct Edge a, struct Edge b) {
		return a.weight > b.weight;
	}
};

class Graph {
public:
	Graph()
	{}

public:
	void AddEdge(int src, int dst, int weight);
	void Initialize();
	void Dijkstra(int start, int end);

private:
	std::map<int, std::vector<struct Edge> > vertex;
	int distance[kVertexNum];
	int path[kVertexNum];

	std::priority_queue<struct Edge, vector<struct Edge>, cmp> p;	
};

void Graph::AddEdge(int src, int dst, int weight) {
	{
		struct Edge edge;
		edge.src    = src;
		edge.dst    = dst;
		edge.weight = weight;
		vertex[edge.src].push_back(edge);
	}

	{
		struct Edge edge;
		edge.src    = dst;
		edge.dst    = src;
		edge.weight = weight;
		vertex[edge.src].push_back(edge);
	}
}

void Graph::Initialize() {
	this->vertex.clear();

 	// Undirected graph
	this->AddEdge(0, 1, 1);
	this->AddEdge(0, 2, 3);
	this->AddEdge(0, 3, 10);
	this->AddEdge(1, 2, 1);
	this->AddEdge(1, 3, 3);
	this->AddEdge(2, 3, 1);
	this->AddEdge(3, 4, 1);
	this->AddEdge(3, 5, 3);
	this->AddEdge(3, 6, 10);
	this->AddEdge(4, 5, 1);
	this->AddEdge(4, 6, 3);
	this->AddEdge(5, 6, 1);

	for (int i = 0; i < kVertexNum; i++) {
		this->distance[i] = INT_MAX;
		this->path[i]     = INT_MAX;
	}
}

void Graph::Dijkstra(int start, int end) {
	if (start+1 > kVertexNum || end+1 > kVertexNum) {
		return;
	}
	
	struct Edge edge;
	edge.src    = start;
	edge.dst    = start;
	edge.weight = 0;

	this->p.push(edge);
	this->distance[start] = 0; 
	int weight            = 0;

	cout << "traverse: ";
	while (!p.empty()) {
		const struct Edge v = this->p.top();
		this->p.pop();

		if (this->path[v.dst] == INT_MAX) {
			this->path[v.dst] = v.src;
			
			cout << v.dst << " ";
		} else {
			// visited
			continue;
		}

		std::map<int, std::vector<struct Edge> >::iterator iter1st = 
			this->vertex.find(v.dst);
		if (iter1st == this->vertex.end()) {
			continue;
		}
		
		std::vector<struct Edge>::iterator iter2nd = iter1st->second.begin();
		for (; iter2nd != iter1st->second.end(); ++iter2nd) {
			weight = iter2nd->weight + v.weight;
			if (weight < distance[iter2nd->dst]) {
				this->distance[iter2nd->dst] = weight;
			
				struct Edge e;
				e.src    = iter2nd->src;
				e.dst    = iter2nd->dst;
				e.weight = weight;
				this->p.push(e);	
			}
		}
	};
	cout << endl;

	cout << "distance: ";
	for (int i = 0; i < kVertexNum; ++i) {
		cout << distance[i] << " ";
	}
	cout << endl;

	std::stack<int> result;
	int src = this->path[end];
	result.push(end);
	if (src != start) {
		result.push(src);
	}
	while (src != start) {
		result.push(this->path[src]);
		src = this->path[src];
	}
	cout << "path:     ";
	while (!result.empty()) {
		cout << result.top() << " ";
		result.pop();
	}
	cout << endl;
}

int main()
{
	Graph graph;
	graph.Initialize();

	// 4 ---> 0
	graph.Dijkstra(4, 0);
}
