# Codility — Lesson 8: Leader

Source: https://app.codility.com/programmers/lessons/8-leader/

Tasks: **Dominator**, **EquiLeader**

---

## Dominator

### Problem (paraphrased)
An array's "dominator" is a value occurring at **more than half** its
indices. Return any index where the dominator occurs, or -1 if there is
none.

### Approach
The Boyer–Moore majority-vote algorithm finds a majority-element
*candidate* in one linear pass (pair off differing values, they cancel).
Then verify the candidate actually occurs more than N/2 times.

```python
def solution(A):
    if not A:
        return -1
    candidate = None
    count = 0
    for value in A:
        if count == 0:
            candidate = value
            count = 1
        elif value == candidate:
            count += 1
        else:
            count -= 1

    occurrences = A.count(candidate)
    if occurrences > len(A) // 2:
        return A.index(candidate)
    return -1
```

**Complexity:** O(N) time, O(1) space.

---

## EquiLeader

### Problem (paraphrased)
Find the number of split points `S` (`0 ≤ S < N-1`) such that the
"leader" (dominator) of `A[0..S]` equals the leader of `A[S+1..N-1]`, and
each half actually has a leader.

### Approach
If the whole array has no leader, there can be no equi-leader split at all.
Otherwise, find the overall leader and its total count, then scan `S` left
to right maintaining a running left-side count of the leader value —
the right-side count follows by subtraction.

```python
def solution(A):
    n = len(A)
    candidate = None
    count = 0
    for value in A:
        if count == 0:
            candidate = value
            count = 1
        elif value == candidate:
            count += 1
        else:
            count -= 1

    leader_count = A.count(candidate)
    if leader_count <= n // 2:
        return 0

    equi_leaders = 0
    left_count = 0
    for s in range(n - 1):
        if A[s] == candidate:
            left_count += 1
        left_len = s + 1
        right_len = n - left_len
        right_count = leader_count - left_count
        if left_count * 2 > left_len and right_count * 2 > right_len:
            equi_leaders += 1
    return equi_leaders
```

**Complexity:** O(N) time, O(1) extra space.
