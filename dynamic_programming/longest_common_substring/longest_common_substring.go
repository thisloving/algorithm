package main

import "fmt"

func longestCommonSubstring(s string, p string) int {
	m := len(s) + 1
	n := len(p) + 1

	dp := make([][]int, m)
	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)
		for j := 0; j < n; j++ {
			dp[i][j] = 0
		}
	}

	maxLen := 0
	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if s[i-1] != p[j-1] {
				continue
			}

			dp[i][j] = dp[i-1][j-1] + 1
			if maxLen < dp[i][j] {
				maxLen = dp[i][j]
			}
		}
	}

	return maxLen
}

func main() {
	s := "abcdefg"
	p := "abc"

	lenght := longestCommonSubstring(s, p)
	fmt.Println(lenght)
}
