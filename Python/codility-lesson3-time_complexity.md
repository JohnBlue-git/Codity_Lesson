# Codility — Lesson 3: Time Complexity

Source: https://app.codility.com/programmers/lessons/3-time_complexity/

Tasks: **FrogJmp**, **PermMissingElem**, **TapeEquilibrium**

---

## FrogJmp

### Problem (paraphrased)
A frog starts at position `X` and wants to reach a position `>= Y`, jumping
exactly `D` units at a time. Return the minimal number of jumps needed.

### Approach
Pure arithmetic — no loop required. The number of jumps is the distance
divided by `D`, rounded **up**.

```python
def solution(X, Y, D):
    distance = Y - X
    return (distance + D - 1) // D
```

**Example:** `X=10, Y=85, D=30` → `3` (10→40→70→100)

**Complexity:** O(1) time and space.

---

## PermMissingElem

### Problem (paraphrased)
Array `A` contains N distinct integers taken from the range `[1..(N+1)]` —
i.e. it's a permutation of `1..N+1` with exactly one value missing. Find
the missing value.

### Approach
The sum of `1..(N+1)` has a closed form. Subtract the actual sum of `A`
from it; what's left is the missing element. Avoids any sorting or hashing.

```python
def solution(A):
    n = len(A)
    expected_sum = (n + 1) * (n + 2) // 2
    return expected_sum - sum(A)
```

**Example:** `A = [2, 3, 1, 5]` → `4`

**Complexity:** O(N) time, O(1) space. (In C/C++/Java, use a 64-bit
accumulator — the expected sum can exceed 32-bit int range for large N.)

---

## TapeEquilibrium

### Problem (paraphrased)
Split array `A` (length N ≥ 2) at some point `P` (`1 ≤ P < N`) into
`A[0..P-1]` and `A[P..N-1]`. Minimize
`|sum(A[0..P-1]) - sum(A[P..N-1])|` over all valid `P`.

### Approach
Compute the total sum once. Walk `P` from 1 to N-1, maintaining a running
left-sum; the right-sum is just `total - left`. Track the smallest
absolute difference seen.

```python
def solution(A):
    total = sum(A)
    left = 0
    best = None
    for i in range(len(A) - 1):
        left += A[i]
        right = total - left
        diff = abs(left - right)
        if best is None or diff < best:
            best = diff
    return best
```

**Example:** `A = [3, 1, 2, 4, 3]` → `1`
(best split is P=3: left = `[3,1,2]` sums to 6, right = `[4,3]` sums to 7, `|6-7| = 1`)

**Complexity:** O(N) time, O(1) space.
