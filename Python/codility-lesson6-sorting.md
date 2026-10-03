# Codility — Lesson 6: Sorting

Source: https://app.codility.com/programmers/lessons/6-sorting/

Tasks: **Distinct**, **MaxProductOfThree**, **Triangle**, **NumberOfDiscIntersections**

---

## Distinct

### Problem (paraphrased)
Return the number of distinct values in array `A`.

### Approach
A set does this directly.

```python
def solution(A):
    return len(set(A))
```

**Complexity:** O(N) average time, O(N) space.

---

## MaxProductOfThree

### Problem (paraphrased)
Given array `A` (length ≥ 3, may contain negatives), find the maximum
possible product of any three elements `A[P] * A[Q] * A[R]`.

### Approach
Sort the array. The maximum triplet product is either the three largest
values, or the two smallest (possibly large-magnitude negatives, whose
product is positive) times the single largest value.

```python
def solution(A):
    A.sort()
    return max(A[-1] * A[-2] * A[-3], A[0] * A[1] * A[-1])
```

**Example:** `A = [-3, 1, 2, -2, 5, 6]` → `60`
(three largest: `2*5*6=60`; two smallest × largest: `-3*-2*6=36` — the max is 60)

**Complexity:** O(N log N) time (dominated by the sort), O(1) extra space.

---

## Triangle

### Problem (paraphrased)
Determine whether any triplet `(P, Q, R)` from array `A` can form the sides
of a triangle, i.e. satisfies the triangle inequality in all directions.
Return 1 if such a triplet exists, 0 otherwise.

### Approach
Sort the array. If a valid triangle exists anywhere, one also exists among
some three **consecutive** elements of the sorted array — so it's enough
to check each consecutive triple once.

```python
def solution(A):
    A.sort()
    for i in range(len(A) - 2):
        if A[i] + A[i + 1] > A[i + 2]:
            return 1
    return 0
```

**Complexity:** O(N log N) time, O(1) extra space.

---

## NumberOfDiscIntersections

### Problem (paraphrased)
N discs are centered at positions `0..N-1` on a line, disc `i` has radius
`A[i]` (so it spans `[i - A[i], i + A[i]]`). Count the number of pairs of
discs that intersect. Return -1 if that count exceeds 10,000,000.

### Approach
Classic sweep-line: compute each disc's start and end, sort starts and
ends independently. Walk through discs in order of start; before counting,
close out (pop) any disc whose end already passed. Every disc still "open"
at that point overlaps the new one.

```python
def solution(A):
    n = len(A)
    starts = sorted(i - A[i] for i in range(n))
    ends = sorted(i + A[i] for i in range(n))

    intersections = 0
    open_discs = 0
    j = 0
    for i in range(n):
        while j < n and ends[j] < starts[i]:
            open_discs -= 1
            j += 1
        intersections += open_discs
        open_discs += 1
        if intersections > 10_000_000:
            return -1
    return intersections
```

**Complexity:** O(N log N) time, O(N) space.
