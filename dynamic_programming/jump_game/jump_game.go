package main

import "fmt"

// dp[j] = OR(dp[i] AND i+a[i] >= j)

func jumpGame(array []int) bool {
	m := len(array)
	dp := make([]bool, m)
	dp[0] = true

	for i := 1; i < m; i++ {
		dp[i] = false
		for j := 0; j < i; j++ {
			if dp[j] && j+array[j] >= i {
				dp[i] = true
				break
			}
		}
	}

	for i := 0; i < m; i++ {
		fmt.Printf("%v ", dp[i])
	}
	fmt.Println()

	return dp[m-1]
}

func main() {
	array := []int{2, 3, 1, 1, 4}
	//array := []int{3, 2, 1, 0, 4}
	fmt.Println(jumpGame(array))
}

// time complexity:  O(N**2)
// space complexity: O(N)
