package ahocorasick

import (
	"strings"
	"unicode/utf8"
)

type AcTrieNode struct {
	children map[rune]*AcTrieNode // parent ---> children
	fail     *AcTrieNode          // fail pointer
	lengths  map[int]struct{}     // words length
	isRoot   bool                 // is root
}

func NewAcTrieNode(isRoot bool) *AcTrieNode {
	return &AcTrieNode{
		children: map[rune]*AcTrieNode{},
		fail:     nil,
		lengths:  make(map[int]struct{}),
		isRoot:   isRoot,
	}
}

func (node *AcTrieNode) backtraceFailNode(code rune) *AcTrieNode {
	child, ok := node.children[code]
	if ok {
		return child
	}

	if node.isRoot {
		return node
	}

	return nil
}

// //////////////////
type Hit struct {
	Begin, End int
	Value      []rune
}

type AcTrie struct {
	root *AcTrieNode
}

func NewAcTrie() *AcTrie {
	t := &AcTrie{
		root: NewAcTrieNode(true),
	}

	return t
}

func (ac *AcTrie) addLengths(current *AcTrieNode, lengths map[int]struct{}) {
	if len(lengths) <= 0 {
		return
	}

	for length := range lengths {
		if length == 0 {
			continue
		}

		current.lengths[length] = struct{}{}
	}
}

func (ac *AcTrie) BuildTrie(keyWords []string) {
	for _, keyWord := range keyWords {
		keyWord = strings.TrimSpace(keyWord)
		ac.insert(keyWord)
	}
}

// build trie
func (ac *AcTrie) insert(word string) {
	characters := []rune(word)
	current := ac.root

	for _, code := range characters {
		if _, ok := current.children[code]; !ok {
			current.children[code] = NewAcTrieNode(false)
		}

		current = current.children[code]
	}

	length := utf8.RuneCountInString(word)
	lengths := make(map[int]struct{})
	lengths[length] = struct{}{}
	ac.addLengths(current, lengths)
}

// build fail pointer
// bfs
func (ac *AcTrie) BuildFailPointer() {
	var queue []*AcTrieNode

	// fail of root's children point to root
	for _, child := range ac.root.children {
		child.fail = ac.root
		queue = append(queue, child)
	}

	// 1、found parent
	// 2、traverse parent's children, find if current child
	// 3、if found current child, current child's fail point to this children
	// 4、if not found current child，check parent is root or not.
	// 5、if root, current child'fail point to root
	// 6、if not root, found parent's fail, repeat 1-6
	for len(queue) > 0 {
		parent := queue[0]
		queue = queue[1:]
		if parent.children == nil {
			continue
		}

		for code, child := range parent.children {
			current := parent.fail
			node := current.backtraceFailNode(code)
			for node == nil {
				current = current.fail
				node = current.backtraceFailNode(code)
			}

			child.fail = node
			ac.addLengths(child, node.lengths)

			queue = append(queue, child)
		}
	}
}

func (ac *AcTrie) getNextChild(parent *AcTrieNode, code rune) *AcTrieNode {
	child := parent.backtraceFailNode(code)
	for child == nil {
		parent = parent.fail
		child = parent.backtraceFailNode(code)
	}

	return child
}

func (ac *AcTrie) Search(content string) []*Hit {
	hits := make([]*Hit, 0)

	contents := []rune(content)
	current := ac.root
	for index, code := range contents {
		current = ac.getNextChild(current, code)
		if len(current.lengths) <= 0 {
			continue
		}

		for length := range current.lengths {
			if length == 0 {
				continue
			}

			hit := &Hit{
				Begin: index + 1 - length,
				End:   index,
				Value: make([]rune, length)}
			copy(hit.Value, contents[index+1-length:index+1])

			hits = append(hits, hit)
		}
	}

	return hits
}
