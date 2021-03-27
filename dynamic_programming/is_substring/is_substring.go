package main

import "fmt"

func isSubstring(s string, p string) bool {
	m := len(s)
	n := len(p)

	dp := make([][]bool, m+1)
	for i := 0; i < m; i++ {
		dp[i] = make([]bool, n)
		for j := 0; j < n; j++ {
			dp[i][j] = false
		}
	}

	dp[0][0] = true
	for i := 0; i < m; i++ {
		dp[i][0] = true
	}

	for j := 0; j < n; j++ {
		dp[0][j] = false
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if s[i] == p[j] {
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
