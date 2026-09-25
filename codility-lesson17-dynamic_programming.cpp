// Codility Lesson 17: Dynamic programming
// Tasks: NumberSolitaire, MinAbsSum

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <climits>
using namespace std;

// NumberSolitaire
// Forward DP: best score reaching field i is A[i] plus the best score among
// the 6 fields that could jump to it.
// O(N) time (fixed window of at most 6), O(N) space.
int solution_NumberSolitaire(vector<int> &A) {
    int n = (int)A.size();
    vector<long long> dp(n, LLONG_MIN);
    dp[0] = A[0];
    for (int i = 1; i < n; i++) {
        long long best = LLONG_MIN;
        for (int j = max(0, i - 6); j < i; j++) {
            best = max(best, dp[j]);
        }
        dp[i] = A[i] + best;
    }
    return (int)dp[n - 1];
}

// MinAbsSum
// Assigning signs is equivalent to partitioning |A[i]| into two groups;
// find a subset sum as close as possible to half the total (0/1 knapsack
// reachability).
// O(N * total) time where total = sum(|A[i]|), O(total) space.
int solution_MinAbsSum(vector<int> &A) {
    vector<int> values;
    long long total = 0;
    for (int x : A) {
        int v = abs(x);
        values.push_back(v);
        total += v;
    }

    vector<bool> reachable(total + 1, false);
    reachable[0] = true;
    for (int v : values) {
        for (long long s = total; s >= v; s--) {
            if (reachable[s - v]) reachable[s] = true;
        }
    }

    long long best = total;
    for (long long s = 0; s <= total; s++) {
        if (reachable[s]) {
            best = min(best, (long long)llabs(total - 2 * s));
        }
    }
    return (int)best;
}
