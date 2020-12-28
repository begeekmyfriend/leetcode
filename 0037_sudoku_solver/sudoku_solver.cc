#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        int size = board.size();
        vector<vector<bool>> rows(size, vector<bool>(10));
        vector<vector<bool>> cols(size, vector<bool>(10));
        vector<vector<bool>> boxes(size, vector<bool>(10));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0';
                    int idx = i / 3 * 3 + j / 3;
                    rows[i][num] = true;
                    cols[j][num] = true;
                    boxes[idx][num] = true;
                }
            }
        }

        dfs(board, 0, rows, cols, boxes);
    }

private:
    bool valid(int num, int row, int col, int idx, vector<vector<bool>>& rows,
               vector<vector<bool>>& cols, vector<vector<bool>>& boxes) {
        return !rows[row][num] && !cols[col][num] && !boxes[idx][num];
    }

    bool dfs(vector<vector<char>>& board, int size, vector<vector<bool>>& rows,
             vector<vector<bool>>& cols, vector<vector<bool>>& boxes) {
        if (size == 9 * 9) {
            return true;
        } else {
            bool ok = false;
            int row = size / 9;
            int col = size % 9;
            int idx = row / 3 * 3 + col / 3;
            if (board[row][col] == '.') {
                for (int i = 1; i <= 9; i++) {
                    if (valid(i, row, col, idx, rows, cols, boxes)) {
                        /* lock this grid as well as the number */
                        board[row][col] = i + '0';
                        rows[row][i] = true;
                        cols[col][i] = true;
                        boxes[idx][i] = true;
                        ok = dfs(board, size + 1, rows, cols, boxes);
                        if (!ok) {
                            /* release this grid as well as the number */
                            rows[row][i] = false;
                            cols[col][i] = false;
                            boxes[idx][i] = false;
                            board[row][col] = '.';
                        }
                    }
                }
            } else {
                ok = dfs(board, size + 1, rows, cols, boxes);
            }
            return ok;
        }
    }
};
