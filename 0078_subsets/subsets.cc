#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        dfs(nums, 0, res);
        return res;    
    }

private:
    vector<int> stack;
    void dfs(vector<int>& nums, int start, vector<vector<int>>& res) {
        res.push_back(stack);
        for (int i = start; i < nums.size(); i++) {
            stack.push_back(nums[i]);
            dfs(nums, i + 1, res);
            stack.pop_back();
        }
    }
};
