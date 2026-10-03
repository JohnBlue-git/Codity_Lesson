# Codility — Lesson 12: Euclidean algorithm

Source: https://app.codility.com/programmers/lessons/12-euclidean_algorithm/

Tasks: **ChocolatesByNumbers**, **CommonPrimeDivisors**

---

## ChocolatesByNumbers

### Problem (paraphrased)
`N` chocolates are arranged in a circle, numbered `0..N-1`. Starting at 0,
you eat a chocolate then move `M` positions forward (wrapping around), and
repeat until you land on a chocolate you've already eaten. Return how many
distinct chocolates you eat.

### Approach
This is a pure number-theory result: the number of distinct positions
visited before repeating equals `N / gcd(N, M)`.

```python
from math import gcd

def solution(N, M):
    return N // gcd(N, M)
```

**Complexity:** O(log(min(N, M))) time (Euclid's algorithm), O(1) space.

---

## CommonPrimeDivisors

### Problem (paraphrased)
Given two arrays `A` and `B` of the same length, count how many pairs
`(A[i], B[i])` have **exactly the same set of prime divisors**.

### Approach
To check if `a` and `b` share the same prime divisors: repeatedly strip
from `a` every prime factor it shares with `b` by dividing out
`gcd(a, current_gcd)` until nothing more can be removed. If what's left of
both `a` and `b` is 1, they have identical prime-divisor sets.

```python
from math import gcd

def strip_common_factors(x, d):
    while d != 1:
        d = gcd(x, d)
        x //= d
    return x

def solution(A, B):
    count = 0
    for a, b in zip(A, B):
        d = gcd(a, b)
        if strip_common_factors(a, d) == 1 and strip_common_factors(b, d) == 1:
            count += 1
    return count
```

**Example check:** `a=15 (3*5), b=75 (3*5*5)` → same prime set `{3,5}` → counted.
`a=3, b=6 (2*3)` → different sets → not counted.

**Complexity:** O(M · log²(max value)) time, O(1) space.
