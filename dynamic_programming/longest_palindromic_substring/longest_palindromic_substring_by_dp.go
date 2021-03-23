package main

import "fmt"

func longestPalindrome(s string) string {
	lenght := len(s)
	dp := make([][]bool, lenght, lenght)
	for i := 0; i < lenght; i++ {
		dp[i] = make([]bool, lenght, lenght)
	}

	for i := 0; i < lenght; i++ {
		dp[i][i] = true
	}

	maxLen := 1
	begin := 0
	for j := 1; j < lenght; j++ {
		for i := 0; i < j; i++ {
			if s[i] != s[j] {
				dp[i][j] = false
			} else {
				if j-i < 3 { // (j-1) - (i+1) + 1 < 2
					dp[i][j] = true
				} else {
					dp[i][j] = dp[i+1][j-1]
				}
			}

			if dp[i][j] == true && j-i+1 > maxLen {
				maxLen = j - i + 1
				begin = i
			}
		}
	}

	return s[begin:maxLen]
}

func main() {
	s := "cbbdbbcccx"
	subStr := longestPalindrome(s)
	fmt.Println(subStr)
}

// Time complexity:  O(n**2)
// Space complexity: O(n**2)