package util

import "fmt"

// DFS
// Time: O(v+e)
// Space: O(v)

type DirectedGraph struct {
	graph    map[int][]int
	node     map[int]struct{} // parentNode
	printLog bool
}

func NewDirectedGraph(params ...bool) *DirectedGraph {
	directedGraph := &DirectedGraph{
		graph: make(map[int][]int),
		node:  make(map[int]struct{}),
	}

	if len(params) > 0 && params[0] {
		directedGraph.printLog = true
	}

	return directedGraph
}

func (g *DirectedGraph) AddNode(parentNode, childNode int) {
	if _, ok := g.graph[parentNode]; !ok {
		g.graph[parentNode] = make([]int, 0)
	}

	g.graph[parentNode] = append(g.graph[parentNode], childNode)
	g.node[parentNode] = struct{}{}
}

func (g *DirectedGraph) IsDirectedGraphCycle() bool {
	visiting := map[int]bool{}
	visited := map[int]bool{}

	if g.printLog {
		fmt.Println("node: ", g.node)
	}

	for node := range g.node {
		if g.printLog {
			fmt.Println("------------------------------------------")
			fmt.Println("dfs node ", node)
		}
		if g.detectCycle(node, visiting, visited) {
			return true
		}
	}

	return false
}

func (g *DirectedGraph) detectCycle(node int, visiting, visited map[int]bool) bool {

	if _, found := visited[node]; found {
		if g.printLog {
			fmt.Printf("node %d is already visited -> skip\n", node)
		}
		return false
	}

	// found himself again while recursoin, cycle
	if _, found := visiting[node]; found {
		if g.printLog {
			fmt.Printf("node %d is in visiting -> a cycle is detected\n\n", node)
		}
		return true
	}

	visiting[node] = true
	if g.printLog {
		fmt.Printf("nodes in visiting: %+v\n", visiting)
		fmt.Printf("nodes in visited : %+v\n\n", visited)
	}
	for _, child := range g.graph[node] {
		if g.printLog {
			fmt.Printf("current node: node %d\n", node)
			fmt.Printf("visit  child: node %d\n", child)
		}
		if g.detectCycle(child, visiting, visited) {
			return true
		}
	}

	delete(visiting, node)
	visited[node] = true

	if g.printLog {
		fmt.Printf("finish explore node %d\n", node)
		fmt.Printf("nodes in visiting: %+v\n", visiting)
		fmt.Printf("nodes in visited : %+v\n\n", visited)
	}
	return false
}
