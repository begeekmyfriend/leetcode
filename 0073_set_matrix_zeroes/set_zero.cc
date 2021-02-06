#include <bits/stdc++.h>

using namespace std;

public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool bRow = false, bCol = false;
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[row].size(); col++) {
                if (matrix[row][col] == 0) {
                    if (row == 0) { bRow = true; }
                    if (col == 0) { bCol = true; }
                    matrix[0][col] = matrix[row][0] = 0;
                }
            }
        }

        for (int row = 1; row < matrix.size(); row++) {
            for (int col = 1; col < matrix[row].size(); col++) {
                if (matrix[0][col] == 0 || matrix[row][0] == 0) {
                    matrix[row][col] = 0;
                }
            }
        }

        if (bRow) {
            for (auto& m : matrix[0]) {
                m = 0;
            }
        }

        if (bCol) {
            for (int row = 0; row < matrix.size(); row++) {
                matrix[row][0] = 0;
            }
        }
    }
};
