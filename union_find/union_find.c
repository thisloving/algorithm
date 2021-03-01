#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Edge {
	int src, dst;
};

struct Graph {
	int V, E;
	struct Edge* edge;
};

struct Graph* create_graph(const int v, const int e) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = v;
	graph->E = e;

	graph->edge = (struct Edge*)malloc(e * sizeof(struct Edge));

	return graph;
}

void initialize(struct Graph* graph) {
	if (graph == NULL) {
		return;
	}

	graph->edge[0].src = 0;
	graph->edge[0].dst = 1;

	graph->edge[1].src = 1;
	graph->edge[1].dst = 2;

	graph->edge[2].src = 0;
	graph->edge[2].dst = 2;
}

int find_root(int parent[], int i) {
	if (parent[i] == -1) {
		return i;
	}

	return find_root(parent, parent[i]);
}

int union_vertices(int parent[], int x, int y, int rank[]) {
	int x_root = find_root(parent, x);
	int y_root = find_root(parent, y);

	//printf("x:%d x_root:%d y:%d y_root:%d\n", x, x_root, y, y_root);
	if (x_root == y_root) {
		return 0;
	} else {
		if (rank[x_root] > rank[y_root]) {
			parent[y_root] = x_root;	
		} else if (rank[y_root] > rank[x_root]){
			parent[x_root] = y_root;
		} else {
			parent[x_root] = y_root;
			rank[y_root]++;
		}
		return 1;
	}
}

bool is_cycle(int parent[], int rank[], struct Graph* graph) {
	if (parent == NULL || graph == NULL) {
		return false;
	}

	int i = 0;
	int x = 0;
	int y = 0;
	for (i = 0; i < graph->E; i++) {
		x = graph->edge[i].src;
		y = graph->edge[i].dst;
		if (x == y) {
			printf("vertex is wrong!\n");
			return false;
		}

		if (union_vertices(parent, x, y, rank) == 0) {
			return true;
		}
	}

	return false;
}

int main()
{
	const int v = 3; 
	const int e = 3;

	int* parent = (int*) malloc(v*sizeof(int)); 
	memset(parent, -1, v*sizeof(int));
	
	int* rank = (int*) malloc(v*sizeof(int));
	memset(rank, 0, v*sizeof(int));

	struct Graph* graph = create_graph(v, e);	
	if (graph == NULL) {
		return 0;
	}

	initialize(graph);
	if (is_cycle(parent, rank, graph) == true) {
		printf("graph contains cycle.\n");
	} else {
		printf("graph doesn't contain contain.\n");
	}

	return 0;
}
