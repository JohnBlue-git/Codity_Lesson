// Codility Lesson 13: Fibonacci numbers
// Tasks: Ladder, FibFrog

#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Ladder
// The number of ways to climb n rungs is the (n+1)-th Fibonacci number.
// Precompute modulo 2^30, then mask per query.
// O(max(A) + N) time, O(max(A)) space.
vector<int> solution_Ladder(vector<int> &A, vector<int> &B) {
    int max_n = *max_element(A.begin(), A.end());
    const long long MOD = 1LL << 30;
    vector<long long> fib(max_n + 2, 0);
    fib[1] = 1;
    if (max_n + 1 >= 2) fib[2] = 2;
    for (int i = 3; i <= max_n + 1; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }

    vector<int> result(A.size());
    for (size_t i = 0; i < A.size(); i++) {
        long long mask = (1LL << B[i]) - 1;
        result[i] = (int)(fib[A[i]] & mask);
    }
    return result;
}

// FibFrog
// BFS over positions reachable by Fibonacci-length jumps guarantees the
// first time the far bank is reached is optimal.
// O(N log N) time, O(N) space.
int solution_FibFrog(vector<int> &A) {
    int n = (int)A.size();
    vector<long long> fibs = {1, 2};
    while (fibs.back() < n + 1) {
        fibs.push_back(fibs[fibs.size() - 1] + fibs[fibs.size() - 2]);
    }

    unordered_map<int, int> dist;
    dist[-1] = 0; // -1 represents the starting bank
    queue<int> q;
    q.push(-1);
    while (!q.empty()) {
        int pos = q.front();
        q.pop();
        int d = dist[pos];
        for (long long f : fibs) {
            long long nxt = pos + f;
            if (nxt == n) return d + 1;
            if (nxt >= 0 && nxt < n && A[(size_t)nxt] == 1 && !dist.count((int)nxt)) {
                dist[(int)nxt] = d + 1;
                q.push((int)nxt);
            }
        }
    }
    return -1;
}
