## 埃拉托斯特尼筛法
sieve of Eratosthenes

埃拉托斯特尼筛法，可以用以下的[伪代码](https://zh.wikipedia.org/wiki/伪代码)来表示：

```
Input: an integer n > 1
 
Let A be an array of Boolean values, indexed by integers 2 to n,
initially all set to true.
 
 for i = 2, 3, 4, ..., not exceeding 
  if A[i] is true:
    for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n :
      A[j] := false
 
Output: all i such that A[i] is true.
```

以上算法可以得到小于等于*n*的所有[素数](https://zh.wikipedia.org/wiki/質數)，它的复杂度是O(*n* log log *n*)。