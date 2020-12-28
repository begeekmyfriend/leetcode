#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> stack;
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.end());
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
            int last = INT_MIN;
            for (int i = start; i < candidates.size(); i++) {
                if (last != candidates[i]) {
                    /* No duplicate combinations in different order */
                    stack.push_back(candidates[i]);
                    /* i + 1 limits the candidate range in next levels */
                    dfs(candidates, i + 1, target - candidates[i], stack, res);
                    stack.pop_back();
                }
                last = candidates[i];
            }
        }
    }
};
