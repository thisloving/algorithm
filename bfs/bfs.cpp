#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>

using namespace std;

const static int kVertexNum = 7;

class Graph {
public:
	Graph() : V(0)
	{}

public:
	void AddVertex(int parent, int child);
	void Initialize();
	void BFS(int vertex);

private:
	int V;
	std::map<int, std::vector<int> > vertex; 
	std::queue<int> q;
	std::set<int> visited;
};

void Graph::AddVertex(int parent, int child) {
	this->vertex[parent].push_back(child);
}

void Graph::Initialize() {
	this->AddVertex(0, 1);
	this->AddVertex(0, 2);
	this->AddVertex(1, 3);
	this->AddVertex(1, 4);
	this->AddVertex(2, 5);
	this->AddVertex(2, 6);

	std::queue<int>().swap(this->q);
	this->visited.clear();
}

void Graph::BFS(int vertex) {
	if (this->visited.find(vertex) != this->visited.end()) {
		return;
	}

	this->q.push(vertex);

	while(!this->q.empty()) {
		int v = this->q.front();
		cout << v << " ";
		this->q.pop();

		std::map<int, std::vector<int> >::iterator iter1st = this->vertex.find(v);
		if (iter1st != this->vertex.end()) {
			std::vector<int>::iterator iter2nd = iter1st->second.begin();
			for (; iter2nd != iter1st->second.end(); ++iter2nd) {
				this->visited.insert(*iter2nd);
				this->q.push(*iter2nd);
			}
		}
	}
	cout << endl;
}

int main()
{
	Graph graph;
	graph.Initialize();

	for (int i = 0; i < kVertexNum; i++) {
		graph.BFS(i);
	}
}
