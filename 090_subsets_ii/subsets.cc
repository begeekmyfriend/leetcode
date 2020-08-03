#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> stack;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, stack, res);
        return res;    
    }

private:
    void dfs(vector<int>& nums, int start, vector<int>& stack, vector<vector<int>>& res) {
        res.push_back(stack);
        int last = INT_MIN;
        for (int i = start; i < nums.size(); i++) {
            if (last != nums[i]) {
                /* No duplicate candidate elements at same level position */
                stack.push_back(nums[i]);
                dfs(nums, i + 1, stack, res);
                stack.pop_back();
            }
            last = nums[i];
        }
    }
};
