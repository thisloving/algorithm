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

#if 0
	this->AddVertex(0, 1);	
	this->AddVertex(0, 2);
	this->AddVertex(1, 3);
	this->AddVertex(1, 4);
	this->AddVertex(2, 5);
	this->AddVertex(2, 6);
#else
	this->AddVertex(0, 1);                                                          
	this->AddVertex(0, 2);                                                          
	this->AddVertex(1, 0);                                                          
	this->AddVertex(1, 3);                                                          
	this->AddVertex(2, 0);                                                          
	this->AddVertex(2, 3);                                                          
	this->AddVertex(3, 1);                                                          
	this->AddVertex(3, 2);                                                          
	this->AddVertex(3, 4);                                                          
	this->AddVertex(3, 5);                                                          
	this->AddVertex(4, 3);                                                          
	this->AddVertex(4, 6);                                                          
	this->AddVertex(5, 3);                                                          
	this->AddVertex(5, 6);                                                          
	this->AddVertex(6, 4);                                                          
	this->AddVertex(6, 5);  
#endif

	stack<int>().swap(this->s);
	this->visited.clear();
}

void Graph::DFS(int vertex) {
	if (vertex+1 > kVertexNum) {
		return;
	}

	this->s.push(vertex);
	this->visited.insert(vertex);

	while(!this->s.empty()) {
		int v = this->s.top();
		cout << v << " ";
		this->s.pop();

		std::map<int, std::vector<int> >::iterator iter1st = this->vertex.find(v);
		if (iter1st != this->vertex.end()) {
			std::vector<int>::iterator iter2nd = iter1st->second.begin();
			for (; iter2nd != iter1st->second.end(); ++iter2nd) {
				if (this->visited.find(*iter2nd) != this->visited.end()) {
					continue;
				}

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

	graph.DFS(6);	
}
