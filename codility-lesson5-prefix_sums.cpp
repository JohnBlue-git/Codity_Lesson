// Codility Lesson 5: Prefix Sums
// Tasks: PassingCars, GenomicRangeQuery, MinAvgTwoSlice, CountDiv

#include <vector>
#include <string>
using namespace std;

// PassingCars
// O(N) time, O(1) space.
int solution_PassingCars(vector<int> &A) {
    long long east = 0;
    long long pairs = 0;
    for (int car : A) {
        if (car == 0) {
            east++;
        } else {
            pairs += east;
            if (pairs > 1000000000LL) return -1;
        }
    }
    return (int)pairs;
}

// GenomicRangeQuery
// O((N+M)*4) time, O(N*4) space.
vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
    // S: ... P ... Q ...
    // prefix sum (accumulative sum) of A, C, G, T by index
    size_t n = S.size();
    vector<char> letters{'A', 'C', 'G', 'T'};
    vector<vector<int>> preSum(4, vector<int>(n, 0));
    for (size_t i = 0; i < n; ++i)
    {
        if (i > 0)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                preSum[j][i] = preSum[j][i - 1];
            }
        }
        auto& s = S[i];
        for (size_t j = 0; j < 4; ++j)
        {
            if (s == letters[j])
            {
                preSum[j][i] += 1;
            }
        }
    }
    // check 'A', 'C', 'G', 'T' existence and then fill in the lowest impact value
    size_t m = P.size();
    vector<int> result(m, 0);
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (S[P[i]] != letters[j] &&
                preSum[j][P[i]] == preSum[j][Q[i]])
            {
                continue;
            }
            result[i] = j + 1; // impact value of 'A' 1, 'C' 2, 'G' 3 , 'T' 4
            break;
        }
    }
    return result;
}

// MinAvgTwoSlice
// The minimal-average slice always has length 2 or 3.
// O(N) time, O(1) space.
int solution_MinAvgTwoSlice(vector<int> &A) {
    int n = (int)A.size();
    double best_avg = 1e18;
    int best_idx = 0;
    for (int i = 0; i < n - 1; i++) {
        double avg2 = (A[i] + A[i + 1]) / 2.0;
        if (avg2 < best_avg) {
            best_avg = avg2;
            best_idx = i;
        }
        if (i < n - 2) {
            double avg3 = (A[i] + A[i + 1] + A[i + 2]) / 3.0;
            if (avg3 < best_avg) {
                best_avg = avg3;
                best_idx = i;
            }
        }
    }
    return best_idx;
}

// CountDiv
// O(1) time and space.
int solution_CountDiv(int A, int B, int K) {
    if (A == 0) return B / K + 1;
    return B / K - (A - 1) / K;
}
