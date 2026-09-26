// Codility Lesson 6: Sorting
// Tasks: Distinct, MaxProductOfThree, Triangle, NumberOfDiscIntersections

#include <vector>
#include <algorithm>
using namespace std;

// Distinct
// O(N log N) time (sort-based), O(N) space.
// int solution_Distinct(vector<int> A) {
//     sort(A.begin(), A.end());
//     A.erase(unique(A.begin(), A.end()), A.end());
//     return (int)A.size();
// }
int solution_Distinct(vector<int> A) {
    unordered_set<int> S(A.begin(), A.end());
    return S.size();
}

// MaxProductOfThree
// Sort, then compare the three largest vs the two smallest times the largest.
// O(N log N) time, O(1) extra space.
int solution_MaxProductOfThree(vector<int> A) {
    sort(A.begin(), A.end());
    size_t n = A.size();
    long long maxProduct = (long long)A[n - 1] * A[n - 2] * A[n - 3];
    if (A[1] < 0)
    {
        maxProduct = max(maxProduct, (long long)A[n - 1] * A[0] * A[1]);
    }
    return maxProduct;
}

// Triangle
// If a valid triangle exists anywhere, one exists among three consecutive
// elements once sorted.
// O(N log N) time, O(1) extra space.
int solution_Triangle(vector<int> A) {
    sort(A.begin(), A.end());
    for (size_t i = 0; i + 2 < A.size(); i++) {
        long long a = A[i], b = A[i + 1], c = A[i + 2];
        if (a + b > c) return 1;
    }
    return 0;
}

// NumberOfDiscIntersections
// Sweep-line over sorted disc starts/ends.
// O(N log N) time, O(N) space.
// int solution_NumberOfDiscIntersections(vector<int> &A) {
//     int n = (int)A.size();
//     vector<long long> starts(n), ends(n);
//     for (int i = 0; i < n; i++) {
//         starts[i] = (long long)i - A[i];
//         ends[i] = (long long)i + A[i];
//     }
//     sort(starts.begin(), starts.end());
//     sort(ends.begin(), ends.end());

//     long long intersections = 0;
//     int open_discs = 0;
//     int j = 0;
//     for (int i = 0; i < n; i++) {
//         while (j < n && ends[j] < starts[i]) {
//             open_discs--;
//             j++;
//         }
//         intersections += open_discs;
//         open_discs++;
//         if (intersections > 10000000LL) return -1;
//     }
//     return (int)intersections;
// }
#include <set>
int solution(vector<int> &A) {
    // 'long long' for preventing overflow
    multiset<pair<long long, bool>> S;
    
    for (size_t i = 0; i < A.size(); ++i)
    {
        long long a = A[i];
        S.emplace(i - a, false);
        S.emplace(i + a, true);
    }
    
    long long count = 0;
    long long open = 0;
    for (auto& [pt, closed] : S)
    {
        if (!closed)
        {
            // overlap with「already exsited
            count += open;
            // add itself
            open++;
            
            if (count > 10000000)
            {
                return -1;
            }
        }
        else
        {
            open--;
        }
    }
    
    return count; // don't meed to remove circle itself
}
// 進化版
// 雖然它跟 multiset 長得很像，但關鍵在於 std::sort 處理連續記憶體的 vector 時，CPU 的快取命中率（Cache Hit Rate）非常高。
// 這省去了紅黑樹在記憶體中到處指引、跳躍尋找節點的時間，因此速度依然比 multiset 快上數倍，能輕易在 Codility 上拿下 100% 的分數。
#include <algorithm>
int solution(vector<int> &A) {
    int n = A.size();
    if (n < 2) return 0;

    vector<pair<long long, bool>> events;
    events.reserve(n * 2);

    for (int i = 0; i < n; ++i)
    {
        long long radius = A[i];
        events.emplace_back(i - radius, false);
        events.emplace_back(i + radius, true);
    }
    sort(events.begin(), events.end());

    long long count = 0;
    int open = 0;
    for (const auto& [pt, is_closed] : events)
    {
        if (!is_closed)
        {
            count += open;
            open++;

            if (count > 10000000) {
                return -1;
            }
        } 
        else
        {
            open--;
        }
    }
    return count;
}
