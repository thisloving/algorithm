package main

import "fmt"

func isSubstring(s string, p string) bool {
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
			if s[i-1] == p[j-1] {
				dp[i][j] = dp[i-1][j-1]
			}
		}
	}

	res := false
	for i := 0; i < m; i++ {
		res = res || dp[i][n-1]
	}

	return res
}

func main() {
	s := "xcsdwsdsdabcdwewewwdw"
	p := "abc"

	fmt.Println(isSubstring(s, p))
}
