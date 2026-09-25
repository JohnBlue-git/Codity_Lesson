// Codility Lesson 14: Binary search algorithm
// Tasks: MinMaxDivision, NailingPlanks

#include <vector>
#include <algorithm>
using namespace std;

// MinMaxDivision
// Binary search on the answer: for a candidate max block-sum, greedily
// count blocks needed; adjust the search range based on that count.
// O(N log(sum(A))) time, O(1) extra space.
int solution_MinMaxDivision(int K, int M, vector<int> &A) {
    auto blocks_needed = [&](long long max_sum) -> int {
        int blocks = 1;
        long long current = 0;
        for (int value : A) {
            if (current + value > max_sum) {
                blocks++;
                current = value;
            } else {
                current += value;
            }
        }
        return blocks;
    };

    long long lo = *max_element(A.begin(), A.end());
    long long hi = 0;
    for (int v : A) hi += v;
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (blocks_needed(mid) <= K) hi = mid;
        else lo = mid + 1;
    }
    return (int)lo;
}

// NailingPlanks
// Feasibility is monotonic in k (using more nails is never worse), so
// binary search on k. Each check sorts the first k nails and binary
// searches for a covering nail per plank.
// O((N+M) log(N+M) log M) time.
bool feasible(vector<pair<int,int>> &planks, vector<int> &C, int k) {
    vector<int> used(C.begin(), C.begin() + k);
    sort(used.begin(), used.end());
    for (auto &pl : planks) {
        int a = pl.first, b = pl.second;
        int idx = (int)(lower_bound(used.begin(), used.end(), a) - used.begin());
        if (idx == (int)used.size() || used[idx] > b) return false;
    }
    return true;
}

int solution_NailingPlanks(vector<int> &A, vector<int> &B, vector<int> &C) {
    vector<pair<int,int>> planks;
    for (size_t i = 0; i < A.size(); i++) planks.push_back({A[i], B[i]});

    int lo = 1, hi = (int)C.size();
    if (!feasible(planks, C, hi)) return -1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (feasible(planks, C, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
