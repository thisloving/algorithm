package topological_sorting

import "testing"

func TestTopologicalSort(t *testing.T) {
	g := NewGraph(true)

	g.addEdge(1, 2)
	g.addEdge(1, 3)
	g.addEdge(2, 4)
	g.addEdge(3, 4)
	g.addEdge(4, 5)
	g.addEdge(4, 6)
	g.addEdge(5, 7)
	g.addEdge(6, 7)

	stack := g.topologicalSort()

	t.Log("topo sort:", stack)
}
