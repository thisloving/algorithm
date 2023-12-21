package util

import "testing"

func TestDirectedGraphNoCycle(t *testing.T) {
	g := NewDirectedGraph(true)

	g.AddNode(1101, 1102)
	g.AddNode(1102, 1103)
	g.AddNode(1103, 1104)
	g.AddNode(1104, 1105)
	g.AddNode(1105, 1106)
	g.AddNode(1106, 1107)

	if g.IsDirectedGraphCycle() {
		t.Error("has cycle, error")
	} else {
		t.Log("no cycle")
	}
}

// go test -run="TestDirectedGraphCycle"
func TestDirectedGraphCycle(t *testing.T) {
	g := NewDirectedGraph(true)

	g.AddNode(1101, 1102)
	g.AddNode(1102, 1103)
	g.AddNode(1103, 1104)
	g.AddNode(1104, 1105)
	g.AddNode(1105, 1101)
	g.AddNode(1105, 1102)

	if g.IsDirectedGraphCycle() {
		t.Log("has cycle")
	} else {
		t.Error("no cycle")
	}
}
