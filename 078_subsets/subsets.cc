#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> stack;
        dfs(nums, 0, stack, res);
        return res;    
    }

private:
    void dfs(vector<int>& nums, int start, vector<int>& stack, vector<vector<int>>& res) {
        res.push_back(stack);
        for (int i = start; i < nums.size(); i++) {
            stack.push_back(nums[i]);
            dfs(nums, i + 1, stack, res);
            stack.pop_back();
        }
    }
};
