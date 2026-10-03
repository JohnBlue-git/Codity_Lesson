# Codility — Lesson 9: Maximum slice problem

Source: https://app.codility.com/programmers/lessons/9-maximum_slice_problem/

Tasks: **MaxSliceSum**, **MaxProfit**, **MaxDoubleSliceSum**

---

## MaxSliceSum

### Problem (paraphrased)
Find the maximum possible sum of any non-empty contiguous slice of array
`A` (which may contain negative numbers — at least one element must be
taken).

### Approach
Kadane's algorithm: track the best sum of a slice *ending here*; either
extend the previous slice or start fresh at the current element, whichever
is larger.

```python
def solution(A):
    max_ending = A[0]
    max_slice = A[0]
    for value in A[1:]:
        max_ending = max(value, max_ending + value)
        max_slice = max(max_slice, max_ending)
    return max_slice
```

**Complexity:** O(N) time, O(1) space.

---

## MaxProfit

### Problem (paraphrased)
Given a log of daily stock prices `A`, find the maximum profit from buying
on one day and selling on a later day. Return 0 if no profit is possible.

### Approach
Track the minimum price seen so far while scanning; at each day, the best
possible profit selling *today* is `today's price - minimum so far`.

```python
def solution(A):
    if not A:
        return 0
    min_price = A[0]
    max_profit = 0
    for price in A[1:]:
        max_profit = max(max_profit, price - min_price)
        min_price = min(min_price, price)
    return max_profit
```

**Complexity:** O(N) time, O(1) space.

---

## MaxDoubleSliceSum

### Problem (paraphrased)
A "double slice" removes one element `A[Y]` (with `0 < Y < N-1`) and joins
the two adjacent slices around it: `A[X+1..Y-1]` and `A[Y+1..Z-1]` for some
`0 ≤ X < Y < Z ≤ N-1`. Find the maximum sum of any double slice (either
half may be empty, contributing 0).

### Approach
Precompute, for every position, the best slice sum *ending* there going
forward, and the best slice sum *starting* there going backward (both
clipped at 0, since an empty half is allowed). The answer is the best
combination of a forward-ending value just before some `Y` and a
backward-starting value just after it.

```python
def solution(A):
    n = len(A)
    ending = [0] * n
    starting = [0] * n
    for i in range(1, n - 1):
        ending[i] = max(0, ending[i - 1] + A[i])
    for i in range(n - 2, 0, -1):
        starting[i] = max(0, starting[i + 1] + A[i])

    best = 0
    for y in range(1, n - 1):
        best = max(best, ending[y - 1] + starting[y + 1])
    return best
```

**Complexity:** O(N) time, O(N) space.
