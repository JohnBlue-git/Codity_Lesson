# Codility — Lesson 11: Sieve of Eratosthenes

Source: https://app.codility.com/programmers/lessons/11-sieve_of_eratosthenes/

Tasks: **CountSemiprimes**, **CountNonDivisible**

---

## CountSemiprimes

### Problem (paraphrased)
A semiprime is a product of exactly two primes (possibly equal), e.g.
`4 = 2*2`, `26 = 2*13`. Given ranges `[P[i], Q[i]]`, count how many
semiprimes fall in each range.

### Approach
Build a "smallest prime factor" sieve up to `N` (a variant of the Sieve of
Eratosthenes). A number `n` is semiprime iff, after dividing out its
smallest prime factor once, the remaining quotient is itself prime.
Precompute a prefix-count of semiprimes to answer each range query in O(1).

```python
def solution(N, P, Q):
    smallest_factor = list(range(N + 1))
    i = 2
    while i * i <= N:
        if smallest_factor[i] == i:  # i is prime
            for j in range(i * i, N + 1, i):
                if smallest_factor[j] == j:
                    smallest_factor[j] = i
        i += 1

    def is_semiprime(n):
        if n < 4:
            return False
        p = smallest_factor[n]
        rest = n // p
        return smallest_factor[rest] == rest  # rest is prime

    semiprime_prefix = [0] * (N + 1)
    for n in range(2, N + 1):
        semiprime_prefix[n] = semiprime_prefix[n - 1] + (1 if is_semiprime(n) else 0)

    return [semiprime_prefix[q] - semiprime_prefix[p - 1] for p, q in zip(P, Q)]
```

**Complexity:** O(N log log N + M) time, O(N) space.

---

## CountNonDivisible

### Problem (paraphrased)
For each element of array `A`, count how many *other* elements in `A` are
**not** divisors of it.

### Approach
Build a frequency table of values in `A`. For each distinct value `v`,
find all its divisors (up to `sqrt(v)`) and sum the frequencies of those
that appear in `A` — that gives the count of elements that *are* divisors
of `v`. The answer for each occurrence of `v` is `N` minus that count.

```python
def solution(A):
    n = len(A)
    max_val = max(A)
    count = [0] * (max_val + 1)
    for value in A:
        count[value] += 1

    divisor_hits = {}
    for value in set(A):
        total = 0
        d = 1
        while d * d <= value:
            if value % d == 0:
                total += count[d]
                other = value // d
                if other != d:
                    total += count[other]
            d += 1
        divisor_hits[value] = total

    return [n - divisor_hits[value] for value in A]
```

**Complexity:** O(N · sqrt(max(A))) time, O(N + max(A)) space.
