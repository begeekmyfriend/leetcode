#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        int direction = 0;
        int hor_top = 0;
        int hor_bottom = n - 1;
        int ver_left = 0;
        int ver_right = n - 1;
        int num  = 0;
        while (num < n * n) {
            switch (direction) {
            case 0:
                for (int i = ver_left; i <= ver_right; i++) {
                     matrix[hor_top][i] = ++num;
                }
                hor_top++;
                break;
            case 1:
                for (int i = hor_top; i <= hor_bottom; i++) {
                     matrix[i][ver_right] = ++num;
                }
                ver_right--;
                break;
            case 2:
                for (int i = ver_right; i >= ver_left; i--) {
                     matrix[hor_bottom][i] = ++num;
                }
                hor_bottom--;
                break;
            case 3:
                for (int i = hor_bottom; i >= hor_top; i--) {
                     matrix[i][ver_left] = ++num;
                }
                ver_left++;
                break;
            }
            direction++;
            direction %= 4;
        }
        return matrix;
    }
};
