package detect_cycle_in_undirected_graph

import "testing"

func TestNewUnDirectedGraphNoCycle(t *testing.T) {
	g := NewUnDirectedGraph(true)

	g.AddNode(1101, 1102)
	g.AddNode(1102, 1103)
	g.AddNode(1103, 1104)
	g.AddNode(1104, 1105)
	g.AddNode(1105, 1106)
	g.AddNode(1106, 1107)

	if g.IsUnDirectedGraphCycle() {
		t.Log("has cycle")
	} else {
		t.Log("has no cycle")
	}
}

func TestNewUnDirectedGraphCycle(t *testing.T) {
	g := NewUnDirectedGraph(true)

	g.AddNode(1101, 1102)
	g.AddNode(1102, 1103)
	g.AddNode(1103, 1101)

	if g.IsUnDirectedGraphCycle() {
		t.Log("has cycle")
	} else {
		t.Log("has no cycle")
	}
}
