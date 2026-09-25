// Codility Lesson 11: Sieve of Eratosthenes
// Tasks: CountSemiprimes, CountNonDivisible

#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// CountSemiprimes
// Build a smallest-prime-factor sieve, then a prefix count of semiprimes.
// O(N log log N + M) time, O(N) space.
vector<int> solution_CountSemiprimes(int N, vector<int> &P, vector<int> &Q) {
    vector<int> smallest_factor(N + 1);
    for (int i = 0; i <= N; i++) smallest_factor[i] = i;

    for (long long i = 2; i * i <= N; i++) {
        if (smallest_factor[i] == i) { // i is prime
            for (long long j = i * i; j <= N; j += i) {
                if (smallest_factor[j] == j) smallest_factor[j] = (int)i;
            }
        }
    }

    auto is_semiprime = [&](int n) -> bool {
        if (n < 4) return false;
        int p = smallest_factor[n];
        int rest = n / p;
        return smallest_factor[rest] == rest;
    };

    vector<int> semiprime_prefix(N + 1, 0);
    for (int n = 2; n <= N; n++) {
        semiprime_prefix[n] = semiprime_prefix[n - 1] + (is_semiprime(n) ? 1 : 0);
    }

    vector<int> result(P.size());
    for (size_t i = 0; i < P.size(); i++) {
        result[i] = semiprime_prefix[Q[i]] - semiprime_prefix[P[i] - 1];
    }
    return result;
}

// CountNonDivisible
// For each distinct value, sum frequencies of its divisors present in A.
// O(N * sqrt(max(A))) time, O(N + max(A)) space.
vector<int> solution_CountNonDivisible(vector<int> &A) {
    int n = (int)A.size();
    int max_val = *max_element(A.begin(), A.end());
    vector<int> count(max_val + 1, 0);
    for (int v : A) count[v]++;

    unordered_map<int, int> divisor_hits;
    for (int value : A) {
        if (divisor_hits.count(value)) continue;
        long long total = 0;
        for (long long d = 1; d * d <= value; d++) {
            if (value % d == 0) {
                total += count[d];
                long long other = value / d;
                if (other != d) total += count[other];
            }
        }
        divisor_hits[value] = (int)total;
    }

    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = n - divisor_hits[A[i]];
    }
    return result;
}
