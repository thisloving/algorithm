package main

import (
	"fmt"
	"math"
)

func coinsChange(coins []int, sum int) int {
	m := sum + 1
	n := len(coins)

	dp := make([]int, m)
	dp[0] = 0
	for i := 1; i < m; i++ {
		dp[i] = math.MaxInt64

		for j := 0; j < n; j++ {
			if i >= coins[j] && dp[i-coins[j]] != math.MaxInt64 {
				if dp[i-coins[j]]+1 < dp[i] {
					dp[i] = dp[i-coins[j]] + 1
				}
			}
		}
	}

	if dp[sum] == math.MaxInt64 {
		dp[sum] = -1
	}

	return dp[sum]
}

func main() {
	coins := []int{2, 5, 7}
	sum := 27

	fmt.Println(coinsChange(coins, sum))
}
