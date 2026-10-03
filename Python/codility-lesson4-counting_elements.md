# Codility — Lesson 4: Counting Elements

Source: https://app.codility.com/programmers/lessons/4-counting_elements/

Tasks: **PermCheck**, **FrogRiverOne**, **MissingInteger**, **MaxCounters**

---

## PermCheck

### Problem (paraphrased)
Determine whether array `A` (length N) is a permutation of `1..N` — every
integer from 1 to N appears exactly once. Return 1 if so, 0 otherwise.

### Approach
Use a boolean "seen" array sized N+1. Any value out of range `[1..N]` or seen
twice immediately disqualifies it.

```python
def solution(A):
    n = len(A)
    seen = [False] * (n + 1)
    for value in A:
        if value < 1 or value > n or seen[value]:
            return 0
        seen[value] = True
    return 1
```

**Complexity:** O(N) time, O(N) space.

---

## FrogRiverOne

### Problem (paraphrased)
A frog needs to cross a river of width `X` by stepping only on leaves that
fall over time. `A[t]` is the position the leaf at time `t` falls at. Find
the earliest time `T` such that leaves have appeared at **every** position
`1..X`. Return -1 if it never happens.

### Approach
Track which of the X positions have been covered with a boolean array.
Count distinct positions covered as you scan; stop the moment the count
reaches X.

```python
def solution(X, A):
    seen = [False] * (X + 1)
    covered = 0
    for t, pos in enumerate(A):
        if 1 <= pos <= X and not seen[pos]:
            seen[pos] = True
            covered += 1
            if covered == X:
                return t
    return -1
```

**Example:** `X=5, A=[1,3,1,4,2,3,5,4]` → `6` (leaf at position 5 appears at index 6)

**Complexity:** O(N + X) time, O(X) space.

---

## MissingInteger

### Problem (paraphrased)
Find the smallest positive integer that does **not** occur in array `A`
(which may contain negatives, duplicates, or values out of range).

### Approach
The answer is always in `[1, N+1]` where N = len(A) — you can't have all of
`1..N` occupied by fewer than N slots plus one. Mark which of `1..N+1` appear,
then scan for the first gap.

```python
def solution(A):
    n = len(A)
    present = [False] * (n + 2)
    for value in A:
        if 1 <= value <= n + 1:
            present[value] = True
    for i in range(1, n + 2):
        if not present[i]:
            return i
```

**Example:** `A = [1, 3, 6, 4, 1, 2]` → `5`

**Complexity:** O(N) time, O(N) space.

---

## MaxCounters

### Problem (paraphrased)
You have N counters, all starting at 0, and a sequence of M operations:
- `X` in `[1..N]`: increase counter `X` by 1.
- `X == N+1`: set **every** counter to the current maximum value.

Return the final state of all N counters.

### Approach
Applying "set all to max" naively is O(N) per operation — O(N·M) overall,
too slow. Instead, defer it: keep a `base` value representing the pending
reset, and only "catch up" a counter to `base` the moment it's touched
again. This gives O(N + M).

```python
def solution(N, A):
    counters = [0] * N
    max_counter = 0
    base = 0  # lazily-applied "set all to max" baseline
    for op in A:
        if 1 <= op <= N:
            idx = op - 1
            if counters[idx] < base:
                counters[idx] = base
            counters[idx] += 1
            max_counter = max(max_counter, counters[idx])
        else:  # op == N + 1
            base = max_counter
    return [c if c > base else base for c in counters]
```

**Complexity:** O(N + M) time, O(N) space.
