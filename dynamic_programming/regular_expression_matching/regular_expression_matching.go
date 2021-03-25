package main

import "fmt"

func regularExpressionMatching(s string, p string) bool {
	m := len(s) + 1
	n := len(p) + 1

	dp := make([][]bool, m, m)
	for i := 0; i < m; i++ {
		dp[i] = make([]bool, n, n)
		for j := 0; j < n; j++ {
			dp[i][j] = false
		}
	}

	dp[0][0] = true
	for i := 1; i < m; i++ {
		dp[i][0] = false
	}

	for j := 1; j < n; j++ {
		if string(p[j-1]) == "*" && j >= 2 { // * not at the beginning
			dp[0][j] = dp[0][j-2]
		}
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if p[j-1] == s[i-1] {
				dp[i][j] = dp[i-1][j-1]
			} else if string(p[j-1]) == "." {
				dp[i][j] = dp[i-1][j-1]
			} else if string(p[j-1]) == "*" {
				if p[j-2] == s[i-1] || string(p[j-2]) == "." {
					dp[i][j] = (dp[i-1][j] || dp[i][j-1] || dp[i][j-2])
				} else {
					dp[i][j] = dp[i][j-2]
				}
			} else {
				dp[i][j] = false
			}
		}
	}

	return dp[len(s)][len(p)]
}

func main() {
	s := "abcce"
	p := "a.c*e"

	isMatch := regularExpressionMatching(s, p)
	fmt.Println(isMatch)
}
