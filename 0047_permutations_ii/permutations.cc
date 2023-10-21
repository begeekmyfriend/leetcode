#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<bool> used(nums.size());
        sort(nums.begin(), nums.end());
        dfs(nums, used, res);
        return res;
    }

private:
    vector<int> stack;
    void dfs(vector<int>& nums, vector<bool>& used, vector<vector<int>>& res) {
        if (stack.size() == nums.size()) {
            res.push_back(stack);
        } else {
            for (int i = 0; i < nums.size(); i++) {
                // used marks remaining allowable elements in the next DFS level
                if (!used[i]) {
                    if (i > 0 && !used[i - 1] && nums[i - 1] == nums[i]) {
                        // !used[i - 1] means the upper DFS level does not contain
                        // nums[i - 1] such that we need to exclude the duplicate
                        // enumeration that has been recorded with used[i-1]==true.
                        continue;
                    }
                    stack.push_back(nums[i]);
                    used[i] = true;
                    dfs(nums, used, res);
                    stack.pop_back();
                    used[i] = false;
                }
            }
        }
    }
};
