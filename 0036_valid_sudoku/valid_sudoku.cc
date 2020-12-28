#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        /* check row validity */
        for (int i = 0; i < board.size(); i++) {
            vector<bool> mark(10);
            /* check row validity */
            for (int j = 0; j < board.size(); j++) {
                if (!valid(board, mark, i, j)) {
                    return false;
                }
            }
        }

        /* check column validity */
        for (int j = 0; j < board.size(); j++) {
            vector<bool> mark(10);
            for (int i = 0; i < board.size(); i++) {
                if (!valid(board, mark, i, j)) {
                    return false;
                }
            }
        }

        /* check sub-box validity */
        for (int k = 0; k < board.size(); k++) {
            int sr = k / 3 * 3;
            int sc = (k % 3) * 3;
            vector<bool> mark(10);
            for (int i = sr; i < sr + 3; i++) {
                for (int j = sc; j < sc + 3; j++) {
                    if (!valid(board, mark, i, j)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

private:
    bool valid(vector<vector<char>>& board, vector<bool>& mark, int i, int j) {
        if (board[i][j] != '.') {
            int index = board[i][j] - '0';
            if (mark[index]) {
                return false;
            } else {
                mark[index] = 1;
            }
        }
        return true;
    }
};
