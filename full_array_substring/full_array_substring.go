package main

import (
	"fmt"
)

func fullArraySubstring(s string, noRepeatStr string) int {
	if len(s) == 0 || len(noRepeatStr) == 0 {
		return 0
	}

	left := 0

	m := make(map[string]int)

	for right := 0; right < len(s); right++ {
		isIn := false
		for _, v := range noRepeatStr {
			if string(v) == string(s[right]) {
				isIn = true
				break
			}
		}

		if !isIn {
			// clear
			m = make(map[string]int)
			left = right + 1
			continue
		}

		if pos, ok := m[string(s[right])]; ok {
			for i := left; i <= pos; i++ {
				delete(m, string(s[i]))
			}
			left = pos + 1
		}

		m[string(s[right])] = right

		if len(m) == len(noRepeatStr) {
			// found
			return left
		}
	}

	return -1
}

func main() {
	s := "abcabcabcaadbccbdabcds"
	noRepeatStr := "abcd"

	index := fullArraySubstring(s, noRepeatStr)
	fmt.Println(index)
}
