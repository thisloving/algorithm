package main

import (
	"fmt"
)

func fullArraySubstring(s string, noRepeatStr string) int {
	if len(s) == 0 || len(noRepeatStr) == 0 {
		return 0
	}

	m := make(map[string]int)
	left := 0
	for right := 0; right < len(s); right++ {
		if pos, ok := m[string(s[right])]; ok {
			if left <= pos {
				left = pos + 1
				for i := pos; i < left; i++ {
					delete(m, string(s[i]))
				}
			}
		} else {
			isIn := false
			for _, v := range noRepeatStr {
				if string(v) == string(s[right]) {
					isIn = true
					break
				}
			}

			if !isIn {
				m = make(map[string]int)
				left = right + 1
				continue
			}
		}

		m[string(s[right])] = right
		if len(noRepeatStr) == len(m) {
			return left
		}
	}

	return -1
}

func main() {
	s := "dcbxabctbcacbdata"
	noRepeatStr := "abcd"

	n := fullArraySubstring(s, noRepeatStr)
	fmt.Println(n)
}
