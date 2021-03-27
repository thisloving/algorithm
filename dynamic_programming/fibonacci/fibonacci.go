package main

import "fmt"

func fibonacci(n int) int {
	dp := make([]int, n+1)

	dp[0] = 0
	dp[1] = 1
	dp[2] = 1

	for i := 3; i <= n; i++ {
		dp[i] = dp[i-1] + dp[i-2]
	}

	return dp[n]
}

func main() {
	value := fibonacci(4)
	fmt.Println(value)
}
