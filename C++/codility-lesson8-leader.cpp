// Codility Lesson 8: Leader
// Tasks: Dominator, EquiLeader

#include <vector>
#include <algorithm>
using namespace std;

// Dominator
// Boyer-Moore majority vote finds a candidate in one pass, then verify it.
// O(N) time, O(1) space.
int solution_Dominator(vector<int> &A) {
    if (A.empty()) return -1;
    int candidate = A[0];
    int count = 0;
    for (int v : A) {
        if (count == 0) {
            candidate = v;
            count = 1;
        } else if (v == candidate) {
            count++;
        } else {
            count--;
        }
    }

    int occurrences = 0;
    for (int v : A) if (v == candidate) occurrences++;

    if (occurrences > (int)A.size() / 2) {
        for (size_t i = 0; i < A.size(); i++) {
            if (A[i] == candidate) return (int)i;
        }
    }
    return -1;
}

// EquiLeader
// Find the overall leader and its count, then scan split points left to
// right maintaining a running left-side count.
// O(N) time, O(1) extra space.
int solution_EquiLeader(vector<int> &A) {
    int n = (int)A.size();
    int candidate = A[0];
    int count = 0;
    for (int v : A) {
        if (count == 0) {
            candidate = v;
            count = 1;
        } else if (v == candidate) {
            count++;
        } else {
            count--;
        }
    }

    int leader_count = 0;
    for (int v : A) if (v == candidate) leader_count++;
    if (leader_count <= n / 2) return 0;

    int equi_leaders = 0;
    int left_count = 0;
    for (int s = 0; s < n - 1; s++) {
        if (A[s] == candidate) left_count++;
        int left_len = s + 1;
        int right_len = n - left_len;
        int right_count = leader_count - left_count;
        if ((long long)left_count * 2 > left_len && (long long)right_count * 2 > right_len) {
            equi_leaders++;
        }
    }
    return equi_leaders;
}
