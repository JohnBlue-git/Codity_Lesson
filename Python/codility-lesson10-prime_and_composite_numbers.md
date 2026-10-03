# Codility — Lesson 10: Prime and composite numbers

Source: https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/

Tasks: **CountFactors**, **MinPerimeterRectangle**, **Peaks**, **Flags**

---

## CountFactors

### Problem (paraphrased)
Count the number of divisors of a given integer `N`.

### Approach
Divisors come in pairs `(i, N/i)` with `i ≤ sqrt(N)`. Scan `i` up to
`sqrt(N)`, counting 2 per pair (1 if `i == N/i`, i.e. `N` is a perfect
square).

```python
def solution(N):
    count = 0
    i = 1
    while i * i < N:
        if N % i == 0:
            count += 2
        i += 1
    if i * i == N:
        count += 1
    return count
```

**Complexity:** O(sqrt(N)) time, O(1) space.

---

## MinPerimeterRectangle

### Problem (paraphrased)
Given the area `N` of a rectangle with integer sides, find the minimum
possible perimeter.

### Approach
The most "square-like" factor pair minimizes the perimeter. Scan divisors
up to `sqrt(N)` and take the pair closest together.

```python
def solution(N):
    best = None
    i = 1
    while i * i <= N:
        if N % i == 0:
            j = N // i
            perimeter = 2 * (i + j)
            if best is None or perimeter < best:
                best = perimeter
        i += 1
    return best
```

**Complexity:** O(sqrt(N)) time, O(1) space.

---

## Peaks

### Problem (paraphrased)
A "peak" is an index `P` (not the first or last) where `A[P-1] < A[P] > A[P+1]`.
Split `A` into the maximum number of equal-sized contiguous blocks such
that **every** block contains at least one peak.

### Approach
Only divisors of `N` (the array length) are candidate block counts, and a
valid block count can't exceed the total number of peaks. Precompute a
peak prefix-count array, then try candidate block counts from most peaks
down to 1, checking (via the prefix sums) that every block has ≥1 peak.

```python
def solution(A):
    n = len(A)
    is_peak = [0] * n
    for i in range(1, n - 1):
        if A[i - 1] < A[i] > A[i + 1]:
            is_peak[i] = 1

    prefix = [0] * (n + 1)
    for i in range(n):
        prefix[i + 1] = prefix[i] + is_peak[i]

    total_peaks = prefix[n]
    if total_peaks == 0:
        return 0

    for blocks in range(total_peaks, 0, -1):
        if n % blocks != 0:
            continue
        block_size = n // blocks
        if all(prefix[(b + 1) * block_size] - prefix[b * block_size] > 0
               for b in range(blocks)):
            return blocks
    return 0
```

**Complexity:** O(N log N) time (bounded by the divisor checks), O(N) space.

---

## Flags

### Problem (paraphrased)
A mountain range is given as array `A`. A "peak" is defined as in the Peaks
task above. You can place flags on peaks, but any two flags must be at
least `K` apart (where `K` is the number of flags you're placing). Find the
maximum number of flags you can place.

### Approach
The achievable `K` is bounded by roughly `sqrt(N)` (K flags spaced K apart
span at least `K*(K-1)` positions). So it's enough to try each candidate
`K` up to that bound and greedily place flags on peaks at least `K` apart.

```python
def solution(A):
    n = len(A)
    peaks = [i for i in range(1, n - 1) if A[i - 1] < A[i] > A[i + 1]]
    if not peaks:
        return 0

    max_flags = 1
    k = 2
    while k * (k - 1) // 2 <= len(peaks):
        placed = 0
        last = -n
        for peak in peaks:
            if peak - last >= k:
                placed += 1
                last = peak
        if placed >= k:
            max_flags = k
        k += 1
    return max_flags
```

**Complexity:** O(N · sqrt(N)) time, O(N) space — well within Codility's
time limit for the given constraints.
