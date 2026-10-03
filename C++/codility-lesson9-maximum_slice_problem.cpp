// Codility Lesson 9: Maximum slice problem
// Tasks: MaxSliceSum, MaxProfit, MaxDoubleSliceSum

#include <vector>
#include <algorithm>
using namespace std;

// MaxSliceSum
// Kadane's algorithm.
// O(N) time, O(1) space.
int solution_MaxSliceSum(vector<int> &A) {
    long long max_ending = A[0];
    long long max_slice = A[0];
    for (size_t i = 1; i < A.size(); i++) {
        max_ending = max((long long)A[i], max_ending + A[i]);
        max_slice = max(max_slice, max_ending);
    }
    return (int)max_slice;
}

// MaxProfit
// Track the minimum price seen so far while scanning.
// O(N) time, O(1) space.
int solution_MaxProfit(vector<int> &A) {
    if (A.empty()) return 0;
    int min_price = A[0];
    int max_profit = 0;
    for (size_t i = 1; i < A.size(); i++) {
        max_profit = max(max_profit, A[i] - min_price);
        min_price = min(min_price, A[i]);
    }
    return max_profit;
}

// MaxDoubleSliceSum
// Precompute best forward-ending and backward-starting slice sums (clipped
// at 0), then combine around each removed point Y.
// O(N) time, O(N) space.
int solution_MaxDoubleSliceSum(vector<int> &A) {
    int n = (int)A.size();
    vector<long long> ending(n, 0), starting(n, 0);
    for (int i = 1; i < n - 1; i++) {
        ending[i] = max(0LL, ending[i - 1] + A[i]);
    }
    for (int i = n - 2; i > 0; i--) {
        starting[i] = max(0LL, starting[i + 1] + A[i]);
    }
    long long best = 0;
    for (int y = 1; y < n - 1; y++) {
        best = max(best, ending[y - 1] + starting[y + 1]);
    }
    return (int)best;
}
