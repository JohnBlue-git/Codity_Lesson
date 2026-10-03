# Codility — Lesson 13: Fibonacci numbers

Source: https://app.codility.com/programmers/lessons/13-fibonacci_numbers/

Tasks: **Ladder**, **FibFrog**

---

## Ladder

### Problem (paraphrased)
Count the number of distinct ways to climb a ladder of `A[i]` rungs, using
steps of 1 or 2 rungs at a time, for each query `i`. Return each count
modulo `2^B[i]`.

### Approach
The number of ways to climb `n` rungs is the (n+1)-th Fibonacci number.
Precompute Fibonacci values up to `max(A)`, keeping them modulo `2^30`
(large enough to safely extract any smaller power-of-two modulus
afterward), then answer each query with a final mask.

```python
def solution(A, B):
    max_n = max(A)
    MOD = 1 << 30
    fib = [0] * (max_n + 2)
    fib[1] = 1
    fib[2] = 2
    for i in range(3, max_n + 2):
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD

    return [fib[a] % (1 << b) for a, b in zip(A, B)]
```

**Complexity:** O(max(A) + N) time, O(max(A)) space.

---

## FibFrog

### Problem (paraphrased)
A frog crosses a river represented by array `A` (leaves at positions where
`A[i] = 1`), jumping distances that must be Fibonacci numbers
(1, 2, 3, 5, 8, ...). Find the minimum number of jumps to cross, or -1 if
impossible.

### Approach
This is a shortest-path problem on positions reachable by Fibonacci-length
jumps — BFS explores positions in increasing number of jumps, guaranteeing
the first time the far bank is reached is optimal.

```python
from collections import deque

def solution(A):
    n = len(A)
    fibs = [1, 2]
    while fibs[-1] < n + 1:
        fibs.append(fibs[-1] + fibs[-2])

    dist = {-1: 0}  # -1 represents the starting bank
    queue = deque([-1])
    while queue:
        pos = queue.popleft()
        d = dist[pos]
        for f in fibs:
            nxt = pos + f
            if nxt == n:
                return d + 1
            if 0 <= nxt < n and A[nxt] == 1 and nxt not in dist:
                dist[nxt] = d + 1
                queue.append(nxt)
    return -1
```

**Complexity:** O(N log N) time (each of N positions tried against
O(log N) Fibonacci jump lengths), O(N) space.
