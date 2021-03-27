#include <stdio.h>
#include <stdlib.h>

struct Edge {
	int src;
	int dst;
	int weight;
};

struct Graph {
	int V;
	int E;

	struct Edge* edge;
};

struct subset {
	int parent;
	int rank;
};

struct Graph* createGraph(int v, int e) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = v;
	graph->E = e;
	graph->edge = (struct Edge*) malloc(e* sizeof(struct Edge));
}

void print_edge(struct Graph* graph, const char desc[]) {
	printf("------ begin %s ------\n", desc);
	int i = 0;
	for (i = 0; i < graph->E; i++) {
		printf("%d --- %d --- %d\n", 
			graph->edge[i].src,
			graph->edge[i].dst,
			graph->edge[i].weight);
	}
	printf("------ end   %s ------\n", desc);
}

void intialize(struct Graph* graph) {
	if (graph == NULL) {
		return;
	}

	graph->edge[0].src = 0;
	graph->edge[0].dst = 1;
	graph->edge[0].weight = 10;

	graph->edge[1].src = 0;
	graph->edge[1].dst = 2;
	graph->edge[1].weight = 6;

	graph->edge[2].src = 0;
	graph->edge[2].dst = 3;
	graph->edge[2].weight = 5;

	graph->edge[3].src = 1;
	graph->edge[3].dst = 3;
	graph->edge[3].weight = 15;

	graph->edge[4].src = 2;
	graph->edge[4].dst = 3;
	graph->edge[4].weight = 4;

	print_edge(graph, "intialize");
}

int find_root(struct subset* subsets, int i) {
	if (subsets[i].parent == i) {
		return i;
	}

	return find_root(subsets, subsets[i].parent);
}

void union_vertex(struct subset* subsets, int x_root, int y_root) {
	if (subsets[x_root].rank > subsets[y_root].rank) {
		subsets[y_root].parent = x_root;
	} else if (subsets[x_root].rank < subsets[y_root].rank) {
		subsets[x_root].parent = y_root;
	} else {
		subsets[x_root].parent = y_root;
		subsets[y_root].rank++;
	}
	return;
}

int my_comp(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;

	return x->weight > y->weight;
}

void kruskal(struct Graph* graph, struct subset* subsets) {
	if (graph == NULL || subsets == NULL) {
		return;
	}

	struct Edge* result = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
	int i = 0;
	for (i = 0; i < graph->E; i++) {
		result[i].src    = 0;
		result[i].dst    = 0;
		result[i].weight = 0;
	}
	
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), my_comp);	
	print_edge(graph, "qsort");

	int v = 0;
	for (i = 0; v < graph->V-1 && i < graph->E; i++) {
		int x = graph->edge[i].src;
		int y = graph->edge[i].dst;
		int x_root = find_root(subsets, x);
		int y_root = find_root(subsets, y);

		if (x_root != y_root) {
			union_vertex(subsets, x_root, y_root);

			result[v] = graph->edge[i];
			v++;
		} else {
			// discard
		}
	}

	printf("min cost begin\n");
	int min_cost = 0;
	for (i = 0; i < v; i++) {
		printf("%d --- %d --- %d\n", result[i].src, result[i].dst, result[i].weight);
		min_cost += result[i].weight;
	}
	printf("min cost:%d\n", min_cost);

	return;
}

int main()
{
	int v = 4;
	int e = 5;
	struct Graph* graph = createGraph(v, e);
	intialize(graph);

	struct subset* subsets = (struct subset*) malloc(v*sizeof(struct subset));
	int i = 0;
	for (i = 0; i < v; i++) {
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}

	kruskal(graph, subsets);
}
