# Codility — Lesson 14: Binary search algorithm

Source: https://app.codility.com/programmers/lessons/14-binary_search_algorithm/

Tasks: **MinMaxDivision**, **NailingPlanks**

---

## MinMaxDivision

### Problem (paraphrased)
Split array `A` into `K` contiguous blocks. Minimize the largest sum among
the `K` blocks.

### Approach
"Binary search on the answer": for a candidate maximum block-sum `mid`,
greedily count how many blocks are needed if no block may exceed `mid`
(start a new block whenever adding the next element would overflow it).
If that count is `≤ K`, `mid` is achievable — search lower; otherwise
search higher. The search space is `[max(A), sum(A)]`.

```python
def solution(K, M, A):
    def blocks_needed(max_sum):
        blocks = 1
        current = 0
        for value in A:
            if current + value > max_sum:
                blocks += 1
                current = value
            else:
                current += value
        return blocks

    lo, hi = max(A), sum(A)
    while lo < hi:
        mid = (lo + hi) // 2
        if blocks_needed(mid) <= K:
            hi = mid
        else:
            lo = mid + 1
    return lo
```

**Complexity:** O(N log(sum(A))) time, O(1) extra space.

---

## NailingPlanks

### Problem (paraphrased)
Planks are given as intervals `[A[i], B[i]]`. Nails are available at
positions `C[0], C[1], ...` (usable **in order**, i.e. you may only use the
first `k` nails from `C` for some `k`). Find the minimum `k` such that
every plank contains at least one of the first `k` nails. Return -1 if
even all nails together can't nail every plank.

### Approach
"Using more nails is only ever at least as good" — feasibility is
monotonic in `k`, so binary search on `k`. For a candidate `k`, sort the
first `k` nail positions and, for each plank, binary-search for a nail
inside its range.

```python
import bisect

def solution(A, B, C):
    planks = list(zip(A, B))

    def feasible(k):
        used = sorted(C[:k])
        for a, b in planks:
            idx = bisect.bisect_left(used, a)
            if idx == len(used) or used[idx] > b:
                return False
        return True

    lo, hi = 1, len(C)
    if not feasible(hi):
        return -1
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid):
            hi = mid
        else:
            lo = mid + 1
    return lo
```

**Complexity:** O((N + M) log(N + M) log M) time — a log M binary search,
each check doing an O(k log k) sort plus N binary searches.
