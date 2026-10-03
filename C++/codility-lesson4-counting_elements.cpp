// Codility Lesson 4: Counting Elements
// Tasks: PermCheck, FrogRiverOne, MissingInteger, MaxCounters

#include <vector>
#include <algorithm>
using namespace std;

// PermCheck
// O(N) time, O(N) space.
int solution_PermCheck(vector<int> &A) {
    int n = (int)A.size();
    vector<bool> seen(n + 1, false);
    for (int v : A) {
        if (v < 1 || v > n || seen[v]) return 0;
        seen[v] = true;
    }
    return 1;
}

// FrogRiverOne
// O(N + X) time, O(X) space.
int solution_FrogRiverOne(int X, vector<int> &A) {
    vector<bool> seen(X + 1, false);
    int covered = 0;
    for (size_t t = 0; t < A.size(); t++) {
        int pos = A[t];
        if (pos >= 1 && pos <= X && !seen[pos]) {
            seen[pos] = true;
            covered++;
            if (covered == X) return (int)t;
        }
    }
    return -1;
}

// MissingInteger
// O(N) time, O(N) space.
int solution_MissingInteger(vector<int> &A) {
    int n = (int)A.size();
    vector<bool> present(n + 2, false);
    for (int v : A) {
        if (v >= 1 && v <= n + 1) present[v] = true;
    }
    for (int i = 1; i <= n + 1; i++) {
        if (!present[i]) return i;
    }
    return n + 1; // unreachable
}

// MaxCounters
// Naive "set all to max" is O(N) per op; defer it lazily instead.
// O(N + M) time, O(N) space.
vector<int> solution_MaxCounters(int N, vector<int> &A) {
    vector<int> counters(N, 0);
    int max_counter = 0;
    int base = 0; // lazily-applied "set all to max" baseline
    for (int op : A) {
        if (op >= 1 && op <= N) {
            int idx = op - 1;
            if (counters[idx] < base) counters[idx] = base;
            counters[idx]++;
            max_counter = max(max_counter, counters[idx]);
        } else { // op == N + 1
            base = max_counter;
        }
    }
    for (int i = 0; i < N; i++) {
        if (counters[i] < base) counters[i] = base;
    }
    return counters;
}
