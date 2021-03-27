package main

import "fmt"

// p is the length of palindrome
// -----maxRight---mirror--------------center--------------i---maxRight

// 1、p[mirror] < maxRight-i,  p[i] = p[mirror]     //(p[mirror] < maxRight-i)
// 2、p[mirror] == maxRight-i, p[i] = (maxRight-i)+
// 3、p[mirror] > maxRight-i,  p[i] = maxRight-i

// p[i] = min(p[mirror], maxRight-i), then center spread

func manacher(s string) string {
	if len(s) < 2 {
		return s
	}

	str := "#"
	for _, v := range s {
		str += string(v)
		str += "#"
	}

	mirror := 0
	center := 0
	maxRight := 0

	maxLen := 0
	begin := 0

	length := len(str)
	p := make([]int, length, length)
	for i := 0; i < length; i++ {
		if i < maxRight {
			mirror = 2*center - i // center - (certer-i)
			if p[mirror] < maxRight-i {
				p[i] = p[mirror]
			} else {
				p[i] = maxRight - i
			}
		}

		left := i - (p[i] + 1)
		right := i + (p[i] + 1)
		for left >= 0 && right < length && str[left] == str[right] {
			p[i]++
			left--
			right++
		}

		if i+p[i] > maxRight {
			maxRight = i + p[i]
			center = i
		}

		if p[i] > maxLen {
			maxLen = p[i]
			begin = (i - maxLen) / 2
		}
	}

	return s[begin : begin+maxLen]
}

func main() {
	s := "wewewewerrffffgggfffttsdsdsd"
	subString := manacher(s)
	fmt.Println(subString)
}
