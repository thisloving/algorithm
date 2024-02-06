package double_array_trie

import (
	"sort"
	"strings"
)

const (
	extraSize int = 10
	rootIndex int = 0
	failState int = -1
)

type DoubleArrayTrie struct {
	base  []int
	check []int
}

type AcDoubleArrayTrie struct {
	DoubleArrayTrie
	fail    []int              // fail pointer
	lengths []map[int]struct{} // lengths of words
}

func NewAcDoubleArrayTrie() *AcDoubleArrayTrie {
	return &AcDoubleArrayTrie{
		DoubleArrayTrie: DoubleArrayTrie{
			base:  make([]int, 0),
			check: make([]int, 0),
		},
		fail:    make([]int, 0),
		lengths: make([]map[int]struct{}, 0),
	}
}

// node
type Node struct {
	code       rune
	index      int // index of base and check
	depth      int
	parentBase int // parent's base
	left       int // fist child
	right      int // last child
	end        bool

	children []*Node
}

func NewNode() *Node {
	return &Node{
		code:       0,
		index:      0,
		depth:      0,
		parentBase: 0, // base+code=index
		left:       0,
		right:      0,
		end:        false,

		children: make([]*Node, 0),
	}
}

// start of trie
type Trie struct {
	root *Node
}

// //////////////////////////////////////
func (ac *AcDoubleArrayTrie) resize(newSize int) {
	oldSize := len(ac.base)
	if newSize < oldSize {
		return
	}

	expand := func(src []int, size int) []int {
		dst := make([]int, size, size)
		copy(dst, src)
		return dst
	}

	newSize += extraSize
	ac.base = expand(ac.base, newSize)
	ac.check = expand(ac.check, newSize)
	ac.fail = expand(ac.fail, newSize)

	dst := make([]map[int]struct{}, newSize, newSize)
	copy(dst, ac.lengths)
	ac.lengths = dst
}

func (ac *AcDoubleArrayTrie) BuildTrie(keyWords []string) *Node {
	words := make([][]rune, 0)

	var maxCode rune = 0
	for _, keyWord := range keyWords {
		keyWord = strings.TrimSpace(keyWord)

		if len(keyWord) == 0 {
			continue
		}

		for _, code := range keyWord {
			if code > maxCode {
				maxCode = code
			}
		}

		words = append(words, []rune(keyWord))
	}

	// sort []rune, not string
	sort.Slice(words, func(i, j int) bool {
		minLen := len(words[i])
		if minLen > len(words[j]) {
			minLen = len(words[j])
		}

		for k := 0; k < minLen; k++ {
			if words[i][k] < words[j][k] {
				return true
			} else if words[i][k] > words[j][k] {
				return false
			} else {
				continue
			}
		}

		if len(words[i]) < len(words[j]) {
			return true
		}

		return false
	})

	ac.resize(int(maxCode))

	trie := &Trie{
		root: NewNode(), // root' index is zero
	}
	trie.root.right = len(words)

	queue := make([]*Node, 0)
	queue = append(queue, trie.root)
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		children := ac.getChildren(node, words)

		if len(children) > 0 {
			queue = append(queue, children...)
		}

		ac.setBaseAndCheck(node)

		if node.end {
			length := len(words[node.left])
			lengths := make(map[int]struct{})
			lengths[length] = struct{}{}
			ac.addLens(node.index, lengths)
		}
	}

	return trie.root
}

func (ac *AcDoubleArrayTrie) addLens(index int, lengths map[int]struct{}) {
	for length := range lengths {
		if len(ac.lengths[index]) == 0 {
			ac.lengths[index] = make(map[int]struct{})
		}

		ac.lengths[index][length] = struct{}{}
	}
}

func (ac *AcDoubleArrayTrie) getChildren(parent *Node, words [][]rune) []*Node {
	var preCode rune = 0
	for i := parent.left; i < parent.right; i++ {
		var curCode rune = 0
		if len(words[i]) != parent.depth {
			curCode = words[i][parent.depth]
		} else {
			parent.end = true
		}

		if preCode != curCode {
			node := &Node{
				code:       curCode,
				depth:      parent.depth + 1,
				left:       i,
				parentBase: parent.parentBase,
			}

			if len(parent.children) > 0 {
				parent.children[len(parent.children)-1].right = i
			}
			parent.children = append(parent.children, node)
		}

		preCode = curCode
	}

	if len(parent.children) > 0 {
		parent.children[len(parent.children)-1].right = parent.right
	}

	return parent.children
}

func (ac *AcDoubleArrayTrie) setBaseAndCheck(parent *Node) {
	base := ac.getBase(parent)
	ac.resize(parent.index)
	ac.base[parent.index] = base // may conflict, reset parent's base value
	//fmt.Printf("setBaseAndCheck parent parent.code:%s, parent.index:%-3d, base:%d\n",
	//	string(parent.code), parent.index, base)
	index := 0
	for _, child := range parent.children {
		index = base + int(child.code)
		child.index = index
		child.parentBase = base

		ac.resize(index)
		ac.base[index] = base // placeholder, may not be the corrent base value
		ac.check[index] = parent.index
		//fmt.Printf("setBaseAndCheck child- child.code: %s, parent.index:%-3d, base:%d, index:%d\n",
		//	string(child.code), parent.index, base, index)
	}
}

func (ac *AcDoubleArrayTrie) getBase(parent *Node) int {
	if len(parent.children) == 0 {
		return parent.parentBase
	}

	firstChildCode := int(parent.children[0].code)
	pos := firstChildCode
	base := 0
	for {
	next:
		pos++

		if len(ac.base) > pos && ac.base[pos] != 0 {
			continue
		}

		base = pos - firstChildCode
		for _, child := range parent.children {
			index := base + int(child.code)
			if len(ac.base) > index && ac.base[index] != 0 { // use base array to check, not the check array
				goto next
			}
		}

		break
	}
	return base
}

func (ac *AcDoubleArrayTrie) backtraceFailNode(parentIndex int, code rune) int {
	base := ac.base[parentIndex] // b >= 0
	childIndex := base + int(code)

	if len(ac.base) <= childIndex {
		if parentIndex == rootIndex {
			return rootIndex
		}
		return failState
	}

	if ac.base[childIndex] != 0 && parentIndex == ac.check[childIndex] {
		return childIndex
	}

	if parentIndex == rootIndex {
		return rootIndex
	}

	return failState
}

func (ac *AcDoubleArrayTrie) BuildFailPointer(root *Node) {
	queue := make([]*Node, 0)

	// depth=0 or depth=1, fail pointer point to rootIndex
	ac.fail[root.index] = rootIndex
	for _, child := range root.children {
		ac.fail[child.index] = rootIndex
		queue = append(queue, child)
	}

	for len(queue) > 0 {
		parent := queue[0]
		queue = queue[1:]

		for _, child := range parent.children {
			// parent.index's fail pointer point to failIndex
			parentFailIndex := ac.fail[parent.index]
			failPointer := ac.backtraceFailNode(parentFailIndex, child.code)
			for failPointer == failState {
				parentFailIndex = ac.fail[parentFailIndex]
				failPointer = ac.backtraceFailNode(parentFailIndex, child.code)
			}

			ac.fail[child.index] = failPointer
			if len(ac.lengths[failPointer]) > 0 {
				ac.addLens(child.index, ac.lengths[failPointer])
			}

			queue = append(queue, child)
		}
	}
}

type Hit struct {
	Begin int
	End   int
	Value []rune
}

func (ac *AcDoubleArrayTrie) Search(content []rune) []Hit {
	hits := []Hit{}
	parentIndex := rootIndex
	for index, code := range content {
		failPointer := ac.backtraceFailNode(parentIndex, code)
		for failPointer == failState {
			parentIndex = ac.fail[parentIndex]
			failPointer = ac.backtraceFailNode(parentIndex, code)
		}

		parentIndex = failPointer

		for length := range ac.lengths[failPointer] {
			if length == 0 {
				continue
			}

			hit := Hit{
				Begin: index + 1 - length,
				End:   index,
				Value: make([]rune, length),
			}
			copy(hit.Value, content[index+1-length:index+1])
			hits = append(hits, hit)
		}
	}

	return hits
}
