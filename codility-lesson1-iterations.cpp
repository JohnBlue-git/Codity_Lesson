// Codility Lesson 1: Iterations
// Task: BinaryGap
//
// Longest run of consecutive 0s strictly between two 1s in N's binary form.
// O(log N) time, O(1) space.

int solution(int N) {
    int max_gap = 0;
    int current_gap = -1; // -1 = haven't seen the first 1 bit yet
    while (N > 0) {
        if (N & 1) {
            if (current_gap >= 0) {
                max_gap = (current_gap > max_gap) ? current_gap : max_gap;
            }
            current_gap = 0;
        } else if (current_gap >= 0) {
            current_gap++;
        }
        N >>= 1;
    }
    return max_gap;
}
