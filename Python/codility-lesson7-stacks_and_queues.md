# Codility — Lesson 7: Stacks and Queues

Source: https://app.codility.com/programmers/lessons/7-stacks_and_queues/

Tasks: **Brackets**, **Fish**, **Nesting**, **StoneWall**

---

## Brackets

### Problem (paraphrased)
Determine whether a string containing `(`, `)`, `{`, `}`, `[`, `]` is
properly nested (every opening bracket has a matching closing bracket of
the same type, correctly ordered).

### Approach
Standard stack: push openers, and on a closer, check the top of the stack
matches; if not (or the stack is empty), it's invalid.

```python
def solution(S):
    pairs = {')': '(', ']': '[', '}': '{'}
    stack = []
    for ch in S:
        if ch in '([{':
            stack.append(ch)
        elif ch in ')]}':
            if not stack or stack.pop() != pairs[ch]:
                return 0
    return 1 if not stack else 0
```

**Complexity:** O(N) time, O(N) space.

---

## Fish

### Problem (paraphrased)
N fish move along a river, each with a size `A[i]` and direction `B[i]`
(0 = downstream, 1 = upstream). When two fish moving toward each other
meet, the bigger one eats the smaller (sizes are unique). Fish moving the
same direction never meet. Return how many fish survive.

### Approach
Process left to right with a stack of downstream fish "waiting" to meet an
oncoming upstream fish. When an upstream fish arrives, it fights the stack
top repeatedly (smaller downstream fish get eaten) until either it wins
(survives, keeps fighting older entries) or loses (gets eaten and stops).

```python
def solution(A, B):
    stack = []  # sizes of downstream fish not yet met by an upstream fish
    alive = 0
    for size, direction in zip(A, B):
        if direction == 1:  # upstream
            survives = True
            while stack and survives:
                if stack[-1] < size:
                    stack.pop()       # downstream fish eaten
                else:
                    survives = False  # this upstream fish gets eaten
            if survives:
                alive += 1
        else:  # downstream
            stack.append(size)
    return alive + len(stack)
```

**Complexity:** O(N) time (each fish pushed/popped at most once), O(N) space.

---

## Nesting

### Problem (paraphrased)
Determine whether a string containing only `(` and `)` is properly nested.

### Approach
A simpler special case of Brackets — a running counter suffices, no need
for an actual stack since there's only one bracket type.

```python
def solution(S):
    balance = 0
    for ch in S:
        if ch == '(':
            balance += 1
        else:
            balance -= 1
            if balance < 0:
                return 0
    return 1 if balance == 0 else 0
```

**Complexity:** O(N) time, O(1) space.

---

## StoneWall

### Problem (paraphrased)
Given the heights of a "Manhattan skyline" wall as array `H`, find the
minimum number of rectangular blocks needed to build it (blocks can be
reused in height, stacked, and are as wide as needed).

### Approach
Maintain a stack of "currently open" block heights. For each new height,
pop any taller blocks (they've ended). If the (possibly now-empty) stack
top doesn't match the new height, a new block must start.

```python
def solution(H):
    stack = []
    blocks = 0
    for height in H:
        while stack and stack[-1] > height:
            stack.pop()
        if not stack or stack[-1] < height:
            blocks += 1
            stack.append(height)
        # if stack[-1] == height, the existing block continues — no new block
    return blocks
```

**Complexity:** O(N) amortized time (each height pushed/popped once), O(N) space.
