// Codility Lesson 10: Prime and composite numbers
// Tasks: CountFactors, MinPerimeterRectangle, Peaks, Flags

#include <vector>
using namespace std;

// CountFactors
// Divisors come in pairs (i, N/i) with i <= sqrt(N).
// O(sqrt(N)) time, O(1) space.
int solution_CountFactors(int N) {
    long long count = 0;
    long long i = 1;
    while (i * i < N) {
        if (N % i == 0) count += 2;
        i++;
    }
    if (i * i == N) count += 1;
    return (int)count;
}

// MinPerimeterRectangle
// The most "square-like" factor pair minimizes the perimeter.
// O(sqrt(N)) time, O(1) space.
int solution_MinPerimeterRectangle(int N) {
    int best = -1;
    long long i = 1;
    while (i * i <= N) {
        if (N % i == 0) {
            long long j = N / i;
            int perimeter = (int)(2 * (i + j));
            if (best == -1 || perimeter < best) best = perimeter;
        }
        i++;
    }
    return best;
}

// Peaks
// Only divisors of N are candidate block counts, bounded by total peaks.
// O(N log N) time, O(N) space.
int solution_Peaks(vector<int> &A) {
    int n = (int)A.size();
    vector<int> is_peak(n, 0);
    for (int i = 1; i < n - 1; i++) {
        if (A[i - 1] < A[i] && A[i] > A[i + 1]) is_peak[i] = 1;
    }
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + is_peak[i];

    int total_peaks = prefix[n];
    if (total_peaks == 0) return 0;

    for (int blocks = total_peaks; blocks >= 1; blocks--) {
        if (n % blocks != 0) continue;
        int block_size = n / blocks;
        bool ok = true;
        for (int b = 0; b < blocks; b++) {
            if (prefix[(b + 1) * block_size] - prefix[b * block_size] == 0) {
                ok = false;
                break;
            }
        }
        if (ok) return blocks;
    }
    return 0;
}

// Flags
// The achievable K is bounded by roughly sqrt(N); try each candidate K and
// greedily place flags on peaks at least K apart.
// O(N * sqrt(N)) time, O(N) space.
int solution_Flags(vector<int> &A) {
    int n = (int)A.size();
    vector<int> peaks;
    for (int i = 1; i < n - 1; i++) {
        if (A[i - 1] < A[i] && A[i] > A[i + 1]) peaks.push_back(i);
    }
    if (peaks.empty()) return 0;

    int max_flags = 1;
    int k = 2;
    while ((long long)k * (k - 1) / 2 <= (long long)peaks.size()) {
        int placed = 0;
        int last = -n;
        for (int peak : peaks) {
            if (peak - last >= k) {
                placed++;
                last = peak;
            }
        }
        if (placed >= k) max_flags = k;
        k++;
    }
    return max_flags;
}
