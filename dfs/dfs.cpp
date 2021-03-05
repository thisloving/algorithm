#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>

using namespace std;

const static int kVertexNum = 7;

class Graph {
public:
	Graph() : V(0)
	{}

public:
	void AddVertex(int parent, int child);
	void Initialize();
	void DFS(int vertex);

private:
	int V;
	std::map<int, std::vector<int> > vertex;
	std::stack<int> s;
	std::set<int> visited;
};


void Graph::AddVertex(int parent, int child) {
	this->vertex[parent].push_back(child);
}

void Graph::Initialize() {
	this->V = kVertexNum;
	this->vertex.clear();

	this->AddVertex(0, 1);	
	this->AddVertex(0, 2);
	this->AddVertex(1, 3);
	this->AddVertex(1, 4);
	this->AddVertex(2, 5);
	this->AddVertex(2, 6);

	stack<int>().swap(this->s);
	this->visited.clear();
}

void Graph::DFS(int vertex) {
	if (this->visited.find(vertex) != this->visited.end()) {
		return;
	}

	this->s.push(vertex);

	while(!this->s.empty()) {
		int v = this->s.top();
		cout << v << " ";
		this->s.pop();

		std::map<int, std::vector<int> >::iterator iter1st = this->vertex.find(v);
		if (iter1st != this->vertex.end()) {
			std::vector<int>::iterator iter2nd = iter1st->second.begin();
			for (; iter2nd != iter1st->second.end(); ++iter2nd) {
				this->s.push(*iter2nd);
				this->visited.insert(*iter2nd);
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
		graph.DFS(i);	
	}
}
