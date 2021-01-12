#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, res);
        return res;    
    }

private:
    vector<int> stack;
    void dfs(vector<int>& nums, int start, vector<vector<int>>& res) {
        res.push_back(stack);
        int last = INT_MIN;
        for (int i = start; i < nums.size(); i++) {
            if (last != nums[i]) {
                /* No duplicate candidate elements in the same level position */
                stack.push_back(nums[i]);
                dfs(nums, i + 1, res);
                stack.pop_back();
            }
            last = nums[i];
        }
    }
};
