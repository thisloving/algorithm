package topological_sorting

import "fmt"

type Graph struct {
	edges    map[int][]int
	vertices map[int]struct{}
	printLog bool
}

func NewGraph(params ...bool) *Graph {
	graph := &Graph{
		edges:    make(map[int][]int),
		vertices: make(map[int]struct{}),
		printLog: false,
	}

	if len(params) > 0 && params[0] {
		graph.printLog = true
	}

	return graph
}

func (g *Graph) addEdge(parentNode, childNode int) {
	g.edges[parentNode] = append(g.edges[parentNode], childNode)

	g.vertices[parentNode] = struct{}{}
	g.vertices[childNode] = struct{}{}
}

func (g *Graph) topologicalSortUtil(vertice int, visited map[int]bool, stack []int) []int {
	visited[vertice] = true

	for _, childNode := range g.edges[vertice] {
		if !visited[childNode] {
			if g.printLog {
				fmt.Printf("recursive parentNode:%d, childNode:%d\n",
					vertice, childNode)
			}
			stack = g.topologicalSortUtil(childNode, visited, stack)
		}
	}

	stack = append([]int{vertice}, stack...)
	if g.printLog {
		fmt.Printf("current stack:%v, vertice:%d\n", stack, vertice)
	}
	return stack
}

func (g *Graph) topologicalSort() []int {
	stack := []int{}
	visited := make(map[int]bool)

	for vertice, _ := range g.vertices {
		if !visited[vertice] {
			if g.printLog {
				fmt.Println("visit node:", vertice)
			}
			stack = g.topologicalSortUtil(vertice, visited, stack)
		}
	}

	return stack
}
