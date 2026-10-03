# Codility — Lesson 2: Arrays

Source: https://app.codility.com/programmers/lessons/2-arrays/

Tasks: **OddOccurrencesInArray**, **CyclicRotation**

---

## OddOccurrencesInArray

### Problem (paraphrased)
An array `A` has N elements, N is odd, and every value appears an even number of
times **except one**, which appears an odd number of times. Return that value.

### Approach
XOR every element together. Matching pairs cancel out (`x ^ x = 0`), leaving
only the unpaired value. O(N) time, O(1) space — no sorting or hash map needed.

```python
from functools import reduce
import operator

def solution(A):
    return reduce(operator.xor, A)
```

**Example:** `A = [9, 3, 9, 3, 9, 7, 9]` → `7`

**Complexity:** O(N) time, O(1) space.

---

## CyclicRotation

### Problem (paraphrased)
Given array `A` and integer `K`, rotate `A` to the right by `K` positions and
return the result. E.g. `A = [3, 8, 9, 7, 6]`, `K = 3` → `[9, 7, 6, 3, 8]`.

### Approach
`K` can exceed `len(A)`, so reduce it with `K % len(A)` first. Then the answer
is just the last `K` elements followed by the first `len(A) - K` elements —
a single slice operation, no per-element loop needed.

```python
def solution(A, K):
    n = len(A)
    if n == 0:
        return A
    K %= n
    if K == 0:
        return A[:]
    return A[-K:] + A[:-K]
```

**Complexity:** O(N) time, O(N) space (for the output array).
