package detect_cycle_in_undirected_graph

import "fmt"

//Time: O(v+e)
//Space: O(v)

type UnDirectedGraph struct {
	graph    map[int][]int
	node     map[int]struct{}
	printLog bool
}

func NewUnDirectedGraph(params ...bool) *UnDirectedGraph {
	undirectedGraph := &UnDirectedGraph{
		graph: make(map[int][]int),
		node:  make(map[int]struct{}),
	}

	if len(params) > 0 && params[0] {
		undirectedGraph.printLog = true
	}

	return undirectedGraph
}

func (g *UnDirectedGraph) AddNode(parentNode, childNode int) {
	if _, ok := g.graph[parentNode]; !ok {
		g.graph[parentNode] = make([]int, 0)
	}

	if _, ok := g.graph[childNode]; !ok {
		g.graph[childNode] = make([]int, 0)
	}

	g.graph[parentNode] = append(g.graph[parentNode], childNode)
	g.graph[childNode] = append(g.graph[childNode], parentNode)

	g.node[parentNode] = struct{}{}
	g.node[childNode] = struct{}{}
}

func (g *UnDirectedGraph) IsUnDirectedGraphCycle() bool {
	visited := map[int]bool{}
	parent := -1

	if g.printLog {
		fmt.Println("node:", g.node)
	}

	for node := range g.node {
		if g.printLog {
			fmt.Println("------------------------------------------")
			fmt.Println("dfs node ", node)
		}

		_, found := visited[node]
		if !found && g.detectCycle(node, visited, parent) {
			return true
		}
	}

	return false
}

func (g *UnDirectedGraph) detectCycle(
	node int,
	visited map[int]bool,
	parent int) bool {
	if _, found := visited[node]; found {
		if g.printLog {
			fmt.Printf("node %d has been visited\n\n", node)
		}
		return true
	}

	visited[node] = true
	for _, child := range g.graph[node] {
		if g.printLog {
			fmt.Printf("current node: %d\n", node)
			fmt.Printf("visited: %+v\n", visited)
			fmt.Printf("parent: %d\n", parent)

			if child != parent {
				fmt.Printf("visited child: node %d\n\n", child)
			} else {
				fmt.Printf("not visited child, node %d. It is parent.\n\n", child)
			}
		}

		if child != parent && g.detectCycle(child, visited, node) {
			return true
		}
	}
	return false
}
