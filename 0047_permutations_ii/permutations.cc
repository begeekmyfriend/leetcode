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
                // Used marks only allows remaining elements in DFS levels
                if (!used[i]) {
                    if (i > 0 && !used[i - 1] && nums[i - 1] == nums[i]) {
                        // In case duplicate permutation with same elemements in the same postion
                        // used[i - 1] == true means different level position
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
