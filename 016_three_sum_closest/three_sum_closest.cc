#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 3) {
            return INT_MAX;
        }

        int min_diff = INT_MAX;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0 && nums[i - 1] == nums[i]) { continue; }

            int lo = i + 1;
            int hi = nums.size() - 1;
            while (lo < hi) {
                int diff = nums[i] + nums[lo] + nums[hi] - target;
                if (abs(diff) < abs(min_diff)) {
                    min_diff = diff;
                }
                if (diff < 0) {
                    lo++;
                } else if (diff > 0) {
                    hi--;
                } else {
                    return target;
                }
            }
        }

        return min_diff + target;
    }
};
