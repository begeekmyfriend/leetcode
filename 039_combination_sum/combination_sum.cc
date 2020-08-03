#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> stack;
        vector<vector<int>> res;
        dfs(candidates, 0, target, stack, res);
        return res;
    }

private:
    void dfs(vector<int>& candidates, int start, int target, vector<int>& stack, vector<vector<int>>& res) {
        if (target < 0) {
            return;
        } else if (target == 0) {
            res.push_back(stack);
        } else {
            for (int i = start; i < candidates.size(); i++) {
                stack.push_back(candidates[i]);
                /* The elements in solution can be duplicate for the purpose of the problem */
                dfs(candidates, i, target - candidates[i], stack, res);
                stack.pop_back();
            }
        }
    }
};
