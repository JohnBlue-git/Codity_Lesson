# Codility — Lesson 5: Prefix Sums

Source: https://app.codility.com/programmers/lessons/5-prefix_sums/

Tasks: **PassingCars**, **GenomicRangeQuery**, **MinAvgTwoSlice**, **CountDiv**

---

## PassingCars

### Problem (paraphrased)
Array `A` holds 0s (car heading east) and 1s (car heading west) along a
one-way-per-lane road. Count the number of pairs `(P, Q)` with `P < Q`,
`A[P] = 0`, `A[Q] = 1` (an eastbound car passing a westbound one). Return
-1 if the count exceeds 1,000,000,000.

### Approach
Scan left to right, tracking how many eastbound (0) cars have been seen so
far. Every time a westbound (1) car appears, it pairs with *all* eastbound
cars seen before it — add that count to the running total.

```python
def solution(A):
    east = 0
    pairs = 0
    for car in A:
        if car == 0:
            east += 1
        else:
            pairs += east
            if pairs > 1_000_000_000:
                return -1
    return pairs
```

**Complexity:** O(N) time, O(1) space.

---

## GenomicRangeQuery

### Problem (paraphrased)
A DNA string `S` uses letters A, C, G, T with "impact factors" 1, 2, 3, 4.
For each query range `[P[i], Q[i]]`, return the minimal impact factor of
any nucleotide occurring in that range.

### Approach
Build prefix-count arrays for each of the 4 nucleotides. For a query,
check counts A→C→G→T in order and return the first one whose count in the
range is nonzero — that's the minimum by construction.

```python
def solution(S, P, Q):
    n = len(S)
    impact = {'A': 0, 'C': 1, 'G': 2, 'T': 3}
    prefix = [[0] * 4 for _ in range(n + 1)]
    for i, ch in enumerate(S):
        for k in range(4):
            prefix[i + 1][k] = prefix[i][k]
        prefix[i + 1][impact[ch]] += 1

    result = []
    for p, q in zip(P, Q):
        for k in range(4):
            if prefix[q + 1][k] - prefix[p][k] > 0:
                result.append(k + 1)
                break
    return result
```

**Complexity:** O((N + M) · 4) time, O(N · 4) space — effectively O(N + M).

---

## MinAvgTwoSlice

### Problem (paraphrased)
Find the starting index `P` of the slice of `A` (length ≥ 2) with the
**smallest average value**. If several slices tie, return the smallest `P`.

### Approach
It's a known property that the minimal-average slice always has length 2
or 3 (a longer optimal slice could always be split into a shorter one with
an equal-or-lower average). So it's enough to check every length-2 and
length-3 slice.

```python
def solution(A):
    n = len(A)
    best_avg = None
    best_idx = 0
    for i in range(n - 1):
        avg2 = (A[i] + A[i + 1]) / 2
        if best_avg is None or avg2 < best_avg:
            best_avg = avg2
            best_idx = i
        if i < n - 2:
            avg3 = (A[i] + A[i + 1] + A[i + 2]) / 3
            if avg3 < best_avg:
                best_avg = avg3
                best_idx = i
    return best_idx
```

**Complexity:** O(N) time, O(1) space.

---

## CountDiv

### Problem (paraphrased)
Count the integers within range `[A, B]` (inclusive) that are divisible
by `K`.

### Approach
Closed-form counting: the number of multiples of `K` in `[0, B]` is
`B // K + 1`, and in `[0, A-1]` is `A // K` (careful with `A = 0`).
Subtract.

```python
def solution(A, B, K):
    if A == 0:
        return B // K + 1
    return B // K - (A - 1) // K
```

**Example:** `A=6, B=11, K=2` → `3` (6, 8, 10)

**Complexity:** O(1) time and space.
