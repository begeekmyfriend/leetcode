#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        vector<int> stack(n);
        return dfs(n, 0, stack);
    }

private:
    int dfs(int n, int row, vector<int>& stack) {
        int count = 0;
        if (row == n) {
            return count + 1;
        } else {
            for (int i = 0; i < n; i++) {
                if (row == 0 || !conflict(stack, row, i)) {
                    stack[row] = i;
                    count += dfs(n, row + 1, stack);
                }
            }
            return count;
        }
    }

    bool conflict(vector<int>& stack, int row, int col) {
        for (int i = 0; i < row; i++) {
            /* If occupied or in one line */
            if (col == stack[i] || abs(row - i) == abs(col - stack[i])) {
                return true;
            }
        }
        return false;
    }
}
