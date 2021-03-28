package main

import "fmt"

func uniquePathsWithObstacles(array [][]int, m int, n int) int {
	if m == 0 || n == 0 {
		return 0
	}

	dp := make([][]int, m)
	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)
		for j := 0; j < n; j++ {
			dp[i][j] = 0
		}
	}

	dp[0][0] = 1
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if array[i][j] == 1 {
				dp[i][j] = 0
			} else {
				if i == 0 || j == 0 {
					dp[i][j] = 1
				} else {
					dp[i][j] = 0
					if i-1 >= 0 {
						dp[i][j] += dp[i-1][j]
					}

					if j-1 >= 0 {
						dp[i][j] += dp[i][j-1]
					}
				}
			}
		}
	}

	return dp[m-1][n-1]
}

func main() {
	array := [][]int{
		{0, 0, 0, 1, 0, 7},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0},
	}

	fmt.Println(uniquePathsWithObstacles(array, 5, 6))
}
