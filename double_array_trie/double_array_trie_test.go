package double_array_trie

import (
	"fmt"
	"sort"
	"testing"
)

func TestNewAcDoubleArrayTrieSort(t *testing.T) {
	a := make([][]rune, 0)
	a = append(a, []rune("aquaj"))
	a = append(a, []rune("jack"))
	a = append(a, []rune("ack"))
	a = append(a, []rune("card"))
	a = append(a, []rune("care"))
	sort.Slice(a, func(i, j int) bool {
		length := len(a[i])
		if length > len(a[j]) {
			length = len(a[j])
		}

		for k := 0; k < length; k++ {
			if a[i][k] < a[j][k] {
				return true
			} else if a[i][k] > a[j][k] {
				return false
			} else {
				continue
			}
		}

		if len(a[i]) < len(a[j]) {
			return true
		}

		return false
	})

	for _, v := range a {
		fmt.Printf("%v ", string(v))
	}
	fmt.Println("")
	fmt.Println(a)
}

func TestNewAcDoubleArrayTrie(t *testing.T) {
	ac := NewAcDoubleArrayTrie()

	words := []string{"aquaj", "jack", "ack", "card", "care"}
	root := ac.BuildTrie(words)
	ac.BuildFailPointer(root)

	content := "aquajackcarecardcatdogcancare"
	result := ac.Search([]rune(content))
	for _, res := range result {
		fmt.Printf("%-3d %-3d %s\n", res.Begin, res.End, string(res.Value))
	}
}
