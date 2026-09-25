// Codility Lesson 16: Greedy algorithms
// Tasks: MaxNonoverlappingSegments, TieRopes

#include <vector>
using namespace std;

// MaxNonoverlappingSegments
// Classic interval-scheduling greedy: input is sorted by start, so scan
// once and take a segment whenever its start is strictly after the last
// taken segment's end.
// O(N) time, O(1) space.
int solution_MaxNonoverlappingSegments(vector<int> &A, vector<int> &B) {
    int n = (int)A.size();
    if (n == 0) return 0;
    int count = 1;
    int last_end = B[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > last_end) {
            count++;
            last_end = B[i];
        }
    }
    return count;
}

// TieRopes
// Greedily accumulate lengths left to right; "cut" a finished rope whenever
// the running total reaches K.
// O(N) time, O(1) space.
int solution_TieRopes(int K, vector<int> &A) {
    int count = 0;
    long long current = 0;
    for (int length : A) {
        current += length;
        if (current >= K) {
            count++;
            current = 0;
        }
    }
    return count;
}
