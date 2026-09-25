// Codility Lesson 3: Time Complexity
// Tasks: FrogJmp, PermMissingElem, TapeEquilibrium

#include <vector>
#include <cstdlib>
using namespace std;

// FrogJmp
// O(1) time and space.
int solution_FrogJmp(int X, int Y, int D) {
    long long distance = (long long)Y - X;
    return (int)((distance + D - 1) / D);
}

// PermMissingElem
// O(N) time, O(1) space. Use a 64-bit accumulator to avoid overflow.
int solution_PermMissingElem(vector<int> &A) {
    long long n = (long long)A.size();
    long long expected_sum = (n + 1) * (n + 2) / 2;
    long long actual_sum = 0;
    for (int x : A) actual_sum += x;
    return (int)(expected_sum - actual_sum);
}

// TapeEquilibrium
// O(N) time, O(1) space.
int solution_TapeEquilibrium(vector<int> &A) {
    long long total = 0;
    for (int x : A) total += x;
    long long left = 0;
    long long best = -1;
    for (size_t i = 0; i + 1 < A.size(); i++) {
        left += A[i];
        long long right = total - left;
        long long diff = llabs(left - right);
        if (best == -1 || diff < best) best = diff;
    }
    return (int)best;
}
