#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() >= 3) {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < nums.size() - 2; i++) {
                if (i > 0 && nums[i - 1] == nums[i]) { continue; }
                twoSum(nums.begin() + i + 1, nums.end() - 1, -nums[i], res);
            }
        }
        return res;
    }

private:
    void twoSum(vector<int>::iterator lo, vector<int>::iterator hi, int target, vector<vector<int>>& res) {
        while (lo < hi) {
            int sum = *lo + *hi;
            if (sum < target) {
                lo++;
            } else if (sum > target) {
                hi--;
            } else {
                res.push_back(vector<int> {-target, *lo, *hi});
                while (++lo < hi && *lo == *(lo - 1)) {}
                while (lo < hi-- && *hi == *(hi + 1)) {}
            }
        }
    }
};
