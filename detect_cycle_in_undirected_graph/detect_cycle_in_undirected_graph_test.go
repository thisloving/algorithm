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
		t.Error("has cycle, error")
	} else {
		t.Log("no cycle")
	}
}

func TestNewUnDirectedGraphCycle(t *testing.T) {
	g := NewUnDirectedGraph(true)

	g.AddNode(1101, 1102)
	g.AddNode(1102, 1103)
	g.AddNode(1103, 1104)

	g.AddNode(1105, 1106)
	g.AddNode(1106, 1107)
	g.AddNode(1107, 1105)

	if g.IsUnDirectedGraphCycle() {
		t.Error("has no cycle, error")
	} else {
		t.Log("has cycle")
	}
}
