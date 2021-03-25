package main

import "fmt"

func maximumSubarray(nums []int) int {
	if len(nums) == 0 {
		return 0
	}

	maxSum := -(2 << 32)
	dp := make([]int, len(nums))
	dp[0] = nums[0]
	if maxSum < dp[0] {
		maxSum = dp[0]
	}

	for i := 1; i < len(nums); i++ {
		if dp[i-1] > 0 {
			dp[i] = nums[i] + dp[i-1]
		} else {
			dp[i] = nums[i]
		}

		if maxSum < dp[i] {
			maxSum = dp[i]
		}
	}

	return maxSum
}

func main() {
	nums := []int{1, 2, 3, -4, -5, 6, 7}
	sum := maximumSubarray(nums)

	fmt.Println(sum)
}
