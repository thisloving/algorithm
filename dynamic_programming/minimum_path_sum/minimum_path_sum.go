package main

import "fmt"

func minimumPathSum(array [][]int, m int, n int) int {
	dp := make([][]int, m)
	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)
		for j := 0; j < n; j++ {
			dp[i][j] = 0
		}
	}

	dp[0][0] = array[0][0]
	for i := 1; i < m; i++ {
		dp[i][0] = array[i][0] + dp[i-1][0]
	}

	for i := 1; i < n; i++ {
		dp[0][i] = array[0][i] + dp[0][i-1]
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if dp[i-1][j] < dp[i][j-1] {
				dp[i][j] = array[i][j] + dp[i-1][j]
			} else {
				dp[i][j] = array[i][j] + dp[i][j-1]
			}
		}
	}

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			fmt.Printf("%2d ", dp[i][j])
		}
		fmt.Println()
	}

	return dp[m-1][n-1]
}

func main() {
	array := [][]int{
		{3, 4, 6, 6, 8, 1},
		{2, 7, 4, 9, 2, 1},
		{9, 2, 1, 7, 8, 5},
		{8, 5, 3, 9, 1, 7},
		{9, 7, 5, 3, 1, 3},
	}

	// 6X5
	sum := minimumPathSum(array, 5, 6)
	fmt.Println(sum)
}
