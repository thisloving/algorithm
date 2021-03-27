package main

import "fmt"

func isSubsequence(s string, p string) bool {
	m := len(s) + 1
	n := len(p) + 1

	dp := make([][]bool, m)
	for i := 0; i < m; i++ {
		dp[i] = make([]bool, n)
		for j := 0; j < n; j++ {
			dp[i][j] = false
		}
	}

	dp[0][0] = true
	for i := 1; i < m; i++ {
		dp[i][0] = true
	}

	for j := 1; j < n; j++ {
		dp[0][j] = false
	}

	for j := 1; j < n; j++ {
		for i := 1; i < m; i++ {
			if dp[i-1][j] {
				dp[i][j] = true
			} else if s[i-1] == p[j-1] && dp[i-1][j-1] {
				dp[i][j] = true
			} else {
				dp[i][j] = false
			}
		}
	}

	res := false
	for i := 1; i < m; i++ {
		res = res || dp[i][n-1]
	}

	for j := 0; j < n; j++ {
		for i := 0; i < m; i++ {
			fmt.Printf("%6v", dp[i][j])
		}
		fmt.Println()
	}

	return res
}

func main() {
	s := "abcdefghijklmnop"
	p := "aem"

	fmt.Println(isSubsequence(s, p))
}
