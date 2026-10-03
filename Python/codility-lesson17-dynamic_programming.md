# Codility — Lesson 17: Dynamic programming

Source: https://app.codility.com/programmers/lessons/17-dynamic_programming/

Tasks: **NumberSolitaire**, **MinAbsSum**

---

## NumberSolitaire

### Problem (paraphrased)
On a board of `N` fields each holding a value `A[i]`, a die-driven token
starts at field 0 and must reach field `N-1`, moving forward by 1 to 6
fields on each move. Maximize the total sum of values visited (including
both endpoints).

### Approach
Simple forward DP: the best score reaching field `i` is `A[i]` plus the
best score among the 6 fields that could jump to it.

```python
def solution(A):
    n = len(A)
    dp = [float('-inf')] * n
    dp[0] = A[0]
    for i in range(1, n):
        dp[i] = A[i] + max(dp[max(0, i - 6):i])
    return dp[-1]
```

**Complexity:** O(N) time (each position looks back over a fixed window of
at most 6), O(N) space.

---

## MinAbsSum

### Problem (paraphrased)
Given an array of integers, assign each element a `+` or `-` sign to
minimize the absolute value of the total sum. Return that minimum.

### Approach
Assigning signs is equivalent to partitioning `|A[i]|` values into two
groups; minimizing `|sum|` means finding a subset whose sum is as close as
possible to half the total of absolute values. This is a subset-sum
reachability problem, solved with a boolean DP over achievable sums (like
a 0/1 knapsack).

```python
def solution(A):
    values = [abs(x) for x in A]
    total = sum(values)

    reachable = [False] * (total + 1)
    reachable[0] = True
    for v in values:
        for s in range(total, v - 1, -1):
            if reachable[s - v]:
                reachable[s] = True

    best = total
    for s in range(total + 1):
        if reachable[s]:
            best = min(best, abs(total - 2 * s))
    return best
```

**Complexity:** O(N · total) time where `total = sum(|A[i]|)`, matching
Codility's expected `O(N * max(abs(A)))` bound; O(total) space.
