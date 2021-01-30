#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        for (auto & t : triangle) {
            passed.push_back(vector<bool>(t.size(), false));
            sums.push_back(vector<int>(t.size()));
        }
        return dfs(triangle, 0, 0);
    }
private:
    vector<vector<bool>> passed;
    vector<vector<int>> sums;
    int dfs(vector<vector<int>>& triangle, int row, int col) {
        if (row == triangle.size() - 1) {
            return triangle[row][col];
        } else if (passed[row][col]) {
            return sums[row][col];
        } else {
            int s1 = dfs(triangle, row + 1, col);
            int s2 = dfs(triangle, row + 1, col + 1);
            sums[row][col] = triangle[row][col] + (s1 < s2 ? s1 : s2);
            passed[row][col] = true;
            return sums[row][col];
        }
    }
};
