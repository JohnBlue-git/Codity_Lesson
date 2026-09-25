// Codility Lesson 12: Euclidean algorithm
// Tasks: ChocolatesByNumbers, CommonPrimeDivisors
//
// Requires C++17 for std::gcd (<numeric>).

#include <vector>
#include <numeric>
using namespace std;

// ChocolatesByNumbers
// Number-theory result: distinct positions visited = N / gcd(N, M).
// O(log(min(N, M))) time, O(1) space.
int solution_ChocolatesByNumbers(int N, int M) {
    long long g = gcd((long long)N, (long long)M);
    return (int)(N / g);
}

// CommonPrimeDivisors
// Repeatedly strip shared prime factors out of a using gcd(a, current_gcd)
// until nothing more can be removed; same for b.
// O(M * log^2(max value)) time, O(1) space.
long long strip_common_factors(long long x, long long d) {
    while (d != 1) {
        d = gcd(x, d);
        x /= d;
    }
    return x;
}

int solution_CommonPrimeDivisors(vector<int> &A, vector<int> &B) {
    int count = 0;
    for (size_t i = 0; i < A.size(); i++) {
        long long a = A[i], b = B[i];
        long long d = gcd(a, b);
        if (strip_common_factors(a, d) == 1 && strip_common_factors(b, d) == 1) {
            count++;
        }
    }
    return count;
}
