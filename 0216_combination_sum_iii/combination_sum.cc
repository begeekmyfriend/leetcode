#include <stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        dfs(1, 9, k, n, res);
        return res;
    }
private:
    vector<int> stack;
    void dfs(int start, int size, int k, int target, vector<vector<int>>& res) {
        if (stack.size() == k) {
            if (target == 0) {
                res.push_back(stack);
            }
        } else {
            for (int i = start; i <= size; i++) {
                stack.push_back(i);
                dfs(i + 1, size, k, target - i, res);
                stack.pop_back();
            }
        }
    }
};
