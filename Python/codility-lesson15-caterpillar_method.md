# Codility — Lesson 15: Caterpillar method

Source: https://app.codility.com/programmers/lessons/15-caterpillar_method/

Tasks: **CountDistinctSlices**, **CountTriangles**, **AbsDistinct**, **MinAbsSumOfTwo**

---

## CountDistinctSlices

### Problem (paraphrased)
Given `M` (values in `A` are in range `[0, M]`) and array `A`, count the
number of contiguous slices where all elements are distinct. Cap the
result at 1,000,000,000.

### Approach
The "caterpillar" / two-pointer technique: grow the window (`head`) while
elements stay distinct (tracked with a `seen` array); when a duplicate
would enter, shrink from `tail` until it's gone. Every window position
contributes `head - tail + 1` new distinct slices ending at `head`.

```python
def solution(M, A):
    n = len(A)
    seen = [False] * (M + 1)
    total = 0
    tail = 0
    for head in range(n):
        while seen[A[head]]:
            seen[A[tail]] = False
            tail += 1
        seen[A[head]] = True
        total += head - tail + 1
        if total > 1_000_000_000:
            return 1_000_000_000
    return total
```

**Complexity:** O(N + M) time, O(M) space.

---

## CountTriangles

### Problem (paraphrased)
Count the number of triplets `(P, Q, R)` with `P < Q < R` from array `A`
that satisfy the triangle inequality (`A[P]+A[Q] > A[R]`, and the other
two inequalities automatically hold once sorted).

### Approach
Sort `A`. For each `P`, use a caterpillar-style two-pointer over `Q` and
`R`: as `Q` increases, the furthest valid `R` only moves forward, so it's
never re-scanned from the start. Every `R` position found valid also
makes all `R` values between `Q+1` and that point valid.

```python
def solution(A):
    A.sort()
    n = len(A)
    count = 0
    for p in range(n - 2):
        r = p + 2
        for q in range(p + 1, n - 1):
            r = max(r, q + 1)
            while r < n and A[p] + A[q] > A[r]:
                r += 1
            count += r - q - 1
    return count
```

**Complexity:** O(N²) time (amortized two-pointer per `P`), O(1) extra space.

---

## AbsDistinct

### Problem (paraphrased)
Given a **sorted** array `A` (which may include negative numbers), count
the number of distinct absolute values.

### Approach
Since `A` is sorted, the largest absolute values sit at the two ends. Walk
inward from both ends with two pointers, always advancing whichever side
currently has the larger absolute value (or both, if they're equal),
counting each new absolute value once.

```python
def solution(A):
    n = len(A)
    left, right = 0, n - 1
    count = 0
    prev = None
    while left <= right:
        left_val = abs(A[left])
        right_val = abs(A[right])
        current = max(left_val, right_val)
        if current != prev:
            count += 1
            prev = current
        if left_val > right_val:
            left += 1
        elif right_val > left_val:
            right -= 1
        else:
            left += 1
            right -= 1
    return count
```

**Complexity:** O(N) time, O(1) extra space.

---

## MinAbsSumOfTwo

### Problem (paraphrased)
Given array `A` (may contain negatives), find the minimum possible value
of `|A[P] + A[Q]|` for any `P ≤ Q`.

### Approach
Sort `A`, then use two pointers from both ends. If the current pair sums
negative, move the left pointer up (to increase the sum); if positive,
move the right pointer down; track the best absolute value seen.

```python
def solution(A):
    A.sort()
    n = len(A)
    left, right = 0, n - 1
    best = abs(A[left] + A[right])
    while left <= right:
        s = A[left] + A[right]
        best = min(best, abs(s))
        if s < 0:
            left += 1
        elif s > 0:
            right -= 1
        else:
            break
    return best
```

**Complexity:** O(N log N) time (dominated by the sort), O(1) extra space.
