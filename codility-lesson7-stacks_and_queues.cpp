// Codility Lesson 7: Stacks and Queues
// Tasks: Brackets, Fish, Nesting, StoneWall

#include <vector>
#include <string>
using namespace std;

// Brackets
// O(N) time, O(N) space.
int solution_Brackets(string &S) {
    vector<char> stack;
    for (char ch : S) {
        if (ch == '(' || ch == '[' || ch == '{') {
            stack.push_back(ch);
        } else {
            if (stack.empty()) return 0;
            char top = stack.back();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return 0;
            }
            stack.pop_back();
        }
    }
    return stack.empty() ? 1 : 0;
}

// Fish
// Process left to right with a stack of downstream fish waiting to meet an
// oncoming upstream fish.
// O(N) time (each fish pushed/popped at most once), O(N) space.
int solution_Fish(vector<int> &A, vector<int> &B) {
    vector<int> stack; // sizes of downstream fish not yet met
    int alive = 0;
    for (size_t i = 0; i < A.size(); i++) {
        int size = A[i];
        int direction = B[i];
        if (direction == 1) { // upstream
            bool survives = true;
            while (!stack.empty() && survives) {
                if (stack.back() < size) {
                    stack.pop_back(); // downstream fish eaten
                } else {
                    survives = false; // this upstream fish gets eaten
                }
            }
            if (survives) alive++;
        } else { // downstream
            stack.push_back(size);
        }
    }
    return alive + (int)stack.size();
}

// Nesting
// Simpler special case of Brackets — a running counter suffices.
// O(N) time, O(1) space.
int solution_Nesting(string &S) {
    int balance = 0;
    for (char ch : S) {
        if (ch == '(') {
            balance++;
        } else {
            balance--;
            if (balance < 0) return 0;
        }
    }
    return balance == 0 ? 1 : 0;
}

// StoneWall
// Maintain a stack of currently open block heights.
// O(N) amortized time, O(N) space.
int solution_StoneWall(vector<int> &H) {
    vector<int> stack;
    int blocks = 0;
    for (int height : H) {
        while (!stack.empty() && stack.back() > height) {
            stack.pop_back();
        }
        if (stack.empty() || stack.back() < height) {
            blocks++;
            stack.push_back(height);
        }
        // if stack.back() == height, the existing block continues
    }
    return blocks;
}
