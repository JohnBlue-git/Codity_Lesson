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
vector<int> solution_GenomicRangeQuery(string &S, vector<int> &P, vector<int> &Q) {
    int n = (int)S.size();
    vector<vector<int>> prefix(n + 1, vector<int>(4, 0));
    auto impact = [](char c) -> int {
        switch (c) {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            default:  return 3; // 'T'
        }
    };
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 4; k++) prefix[i + 1][k] = prefix[i][k];
        prefix[i + 1][impact(S[i])]++;
    }

    vector<int> result;
    result.reserve(P.size());
    for (size_t i = 0; i < P.size(); i++) {
        int p = P[i], q = Q[i];
        for (int k = 0; k < 4; k++) {
            if (prefix[q + 1][k] - prefix[p][k] > 0) {
                result.push_back(k + 1);
                break;
            }
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
