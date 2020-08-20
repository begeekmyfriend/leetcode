#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return vector<int>();
        }

        int hor_top = 0;
        int hor_bottom = matrix.size();
        int ver_left = 0;
        int ver_right = matrix[0].size();
        int direction = 0;
        vector<int> res;

        while (hor_top <= hor_bottom && ver_left <= ver_right) {
            switch (direction) {
            case 0:
                for (int i = ver_left; i <= ver_right; i++) {
                    res.push_back(matrix[hor_top][i]);
                }
                hor_top++;
                break;
            case 1:
                for (int i = hor_top; i <= hor_bottom; i++) {
                    res.push_back(matrix[i][ver_right]);
                }
                ver_right--;
                break;
            case 2:
                for (int i = ver_right; i >= ver_left; i--) {
                    res.push_back(matrix[hor_bottom][i]);
                }
                hor_bottom--;
                break;
            case 3:
                for (int i = hor_bottom; i >= hor_top; i--) {
                    res.push_back(matrix[i][ver_left]);
                }
                ver_left++;
                break;
            default:
                break;
            }
            direction++;
            direction %= 4;
        }

        return res;
    }
};
