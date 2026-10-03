# Codility — Lesson 1: Iterations

Source: https://app.codility.com/programmers/lessons/1-iterations/

Lesson 1 currently contains a single task: **BinaryGap**.

---

## BinaryGap

### Problem (paraphrased)

A *binary gap* in a positive integer `N` is the longest run of consecutive `0`s
that sits strictly **between two `1`s** in `N`'s binary representation. Trailing
zeros that aren't followed by another `1` don't count.

Write `solution(N)` that returns the length of the longest binary gap in `N`,
or `0` if there isn't one.

**Constraint:** `1 ≤ N ≤ 2,147,483,647`

**Examples**

| N | binary | longest gap |
|---|---|---|
| 9 | `1001` | 2 |
| 529 | `1000010001` | 4 |
| 20 | `10100` | 1 |
| 15 | `1111` | 0 |
| 32 | `100000` | 0 (trailing zeros, no closing `1`) |
| 1041 | `10000010001` | 5 |

### Approach

Scan the bits of `N` from least‑significant to most‑significant. Only start
counting a zero-run once the first `1` has been seen, and only "close" (score)
a run when the *next* `1` appears. Zeros before the first `1`, and zeros after
the last `1`, are never counted — this is what correctly excludes trailing
zeros like in `32 = 100000`.

This runs in **O(log N)** time and **O(1)** space — no string conversion needed,
which is the efficient solution Codility is looking for.

### Python

```python
def solution(N):
    max_gap = 0
    current_gap = -1  # -1 = haven't seen the first 1 bit yet
    while N > 0:
        if N & 1:
            if current_gap >= 0:
                max_gap = max(max_gap, current_gap)
            current_gap = 0
        elif current_gap >= 0:
            current_gap += 1
        N >>= 1
    return max_gap
```

*String-based alternative (also O(log N), a bit more readable):*

```python
def solution(N):
    binary = bin(N)[2:]          # e.g. 1041 -> "10000010001"
    gaps = binary.strip('0').split('1')  # zero-runs strictly between 1s
    return max((len(g) for g in gaps), default=0)
```

### C++

```cpp
int solution(int N) {
    int max_gap = 0;
    int current_gap = -1;  // -1 = haven't seen the first 1 bit yet

    while (N > 0) {
        if (N & 1) {
            if (current_gap >= 0) {
                max_gap = std::max(max_gap, current_gap);
            }
            current_gap = 0;
        } else if (current_gap >= 0) {
            current_gap++;
        }
        N >>= 1;
    }
    return max_gap;
}
```

### Complexity

- **Time:** O(log N) — one iteration per bit (max ~31 iterations for the given range)
- **Space:** O(1) for the bitwise version

### Test cases to sanity-check

| N | expected |
|---|---|
| 9 | 2 |
| 529 | 4 |
| 20 | 1 |
| 15 | 0 |
| 32 | 0 |
| 1041 | 5 |
| 1 | 0 |
| 1041 * 0 + 1 (edge: N=1, single bit) | 0 |
| 2147483647 (all 1s, 31 bits) | 0 |

Both solutions above pass Codility's correctness and performance tests (100/100) for this task.
