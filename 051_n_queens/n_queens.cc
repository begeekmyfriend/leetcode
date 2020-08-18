#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> stack(n);
        vector<string> solution(n, string(n, '.'));
        dfs(n, 0, stack, solution, res);
        return res;
    }

private:
    void dfs(int n, int row, vector<int>& stack, vector<string>& solution, vector<vector<string>>& res) {
        if (row == n) {
            res.push_back(solution);
        } else {
            for (int i = 0; i < n; i++) {
                if (row == 0 || !conflict(stack, row, i)) {
                    solution[row][i] = 'Q';
                    stack[row] = i;
                    dfs(n, row + 1, stack, solution, res);
                    solution[row][i] = '.';
                }
            }
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
