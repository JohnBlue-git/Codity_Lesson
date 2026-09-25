// Codility Lesson 15: Caterpillar method
// Tasks: CountDistinctSlices, CountTriangles, AbsDistinct, MinAbsSumOfTwo

#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

// CountDistinctSlices
// Two-pointer "caterpillar": grow head while elements stay distinct; shrink
// tail on a duplicate. Cap the running total at 1,000,000,000.
// O(N + M) time, O(M) space.
int solution_CountDistinctSlices(int M, vector<int> &A) {
    int n = (int)A.size();
    vector<bool> seen(M + 1, false);
    long long total = 0;
    int tail = 0;
    for (int head = 0; head < n; head++) {
        while (seen[A[head]]) {
            seen[A[tail]] = false;
            tail++;
        }
        seen[A[head]] = true;
        total += head - tail + 1;
        if (total > 1000000000LL) return 1000000000;
    }
    return (int)total;
}

// CountTriangles
// Sort, then for each P use a two-pointer over Q and R — R only moves
// forward as Q increases, so it's never re-scanned from the start.
// O(N^2) time (amortized two-pointer per P), O(1) extra space.
int solution_CountTriangles(vector<int> A) {
    sort(A.begin(), A.end());
    int n = (int)A.size();
    long long count = 0;
    for (int p = 0; p < n - 2; p++) {
        int r = p + 2;
        for (int q = p + 1; q < n - 1; q++) {
            r = max(r, q + 1);
            while (r < n && (long long)A[p] + A[q] > A[r]) r++;
            count += r - q - 1;
        }
    }
    return (int)count;
}

// AbsDistinct
// A is sorted; largest absolute values sit at the two ends. Walk inward
// with two pointers, advancing whichever side has the larger absolute value.
// O(N) time, O(1) extra space.
int solution_AbsDistinct(vector<int> &A) {
    int n = (int)A.size();
    int left = 0, right = n - 1;
    int count = 0;
    long long prev = -1;
    bool has_prev = false;
    while (left <= right) {
        long long left_val = abs((long long)A[left]);
        long long right_val = abs((long long)A[right]);
        long long current = max(left_val, right_val);
        if (!has_prev || current != prev) {
            count++;
            prev = current;
            has_prev = true;
        }
        if (left_val > right_val) left++;
        else if (right_val > left_val) right--;
        else { left++; right--; }
    }
    return count;
}

// MinAbsSumOfTwo
// Sort, then two pointers from both ends: move left up if the sum is
// negative, right down if positive.
// O(N log N) time, O(1) extra space.
int solution_MinAbsSumOfTwo(vector<int> A) {
    sort(A.begin(), A.end());
    int n = (int)A.size();
    int left = 0, right = n - 1;
    long long best = abs((long long)A[left] + A[right]);
    while (left <= right) {
        long long s = (long long)A[left] + A[right];
        best = min(best, (long long)abs(s));
        if (s < 0) left++;
        else if (s > 0) right--;
        else break;
    }
    return (int)best;
}
