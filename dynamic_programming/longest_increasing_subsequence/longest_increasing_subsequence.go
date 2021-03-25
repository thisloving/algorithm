package main

import "fmt"

func longestIncreasingSubsequence(nums []int) int {
	dp := make([]int, len(nums), len(nums))
	for i := 0; i < len(nums); i++ {
		dp[i] = 1
	}

	for i := 0; i < len(nums); i++ {
		for j := 0; j < i; j++ {
			if nums[i] <= nums[j] {
				continue
			}

			if dp[i] < dp[j]+1 {
				dp[i] = dp[j] + 1
			}
		}
	}

	res := 0
	for i := 0; i < len(nums); i++ {
		if res < dp[i] {
			res = dp[i]
		}
	}

	return res
}

func main() {
	nums := []int{1, 2, 3, 4, 5, 6, 7}

	length := longestIncreasingSubsequence(nums)
	fmt.Println(length)
}
