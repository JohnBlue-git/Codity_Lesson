# Codility — Lesson 16: Greedy algorithms

Source: https://app.codility.com/programmers/lessons/16-greedy_algorithms/

Tasks: **MaxNonoverlappingSegments**, **TieRopes**

---

## MaxNonoverlappingSegments

### Problem (paraphrased)
Given `N` segments defined by `A[i]` (start) and `B[i]` (end), both sorted
by start position, select the maximum number of segments such that no two
overlap (segments may touch at endpoints).

### Approach
Classic interval-scheduling greedy: always keep the segment that ends
soonest among the candidates, since that leaves the most room for future
segments. Since input is sorted by start, scan once and greedily take a
segment whenever its start is strictly after the last taken segment's end.

```python
def solution(A, B):
    n = len(A)
    if n == 0:
        return 0
    count = 1
    last_end = B[0]
    for i in range(1, n):
        if A[i] > last_end:
            count += 1
            last_end = B[i]
    return count
```

**Complexity:** O(N) time, O(1) space.

---

## TieRopes

### Problem (paraphrased)
Given rope lengths `A` in a row and a target length `K`, you may tie
**adjacent** ropes together (summing their lengths). Find the maximum
number of resulting ropes with length `≥ K`.

### Approach
Greedily accumulate lengths left to right; whenever the running total
reaches `K`, "cut" a finished rope there and reset the accumulator — any
leftover at the very end that doesn't reach `K` just gets tied onto the
previous finished rope (or discarded if nothing follows), which greedy
accumulation naturally achieves.

```python
def solution(K, A):
    count = 0
    current = 0
    for length in A:
        current += length
        if current >= K:
            count += 1
            current = 0
    return count
```

**Complexity:** O(N) time, O(1) space.
