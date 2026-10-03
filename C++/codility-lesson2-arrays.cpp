// Codility Lesson 2: Arrays
// Tasks: OddOccurrencesInArray, CyclicRotation

#include <vector>
using namespace std;

// OddOccurrencesInArray
// XOR all elements; matching pairs cancel out, leaving the unpaired value.
// O(N) time, O(1) space.
int solution_OddOccurrencesInArray(vector<int> &A) {
    int result = 0;
    for (int x : A) result ^= x;
    return result;
}

// CyclicRotation
// Reduce K with K % N, then place each element at its rotated index.
// O(N) time, O(N) space.
vector<int> solution_CyclicRotation(vector<int> &A, int K) {
    int n = (int)A.size();
    if (n == 0) return A;
    K %= n;
    if (K == 0) return A;
    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[(i + K) % n] = A[i];
    }
    return result;
}
