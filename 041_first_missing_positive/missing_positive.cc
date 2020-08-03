#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if (nums.size() == 0) {
            return 1;
        }

        int i = 0;
        while (i < nums.size()) {
            /* nums[i] should be i+1 and nums[nums[i] - 1] should be nums[i] */
            if (nums[i] > 0 && nums[i] != i + 1 && nums[i] - 1 < nums.size() && nums[nums[i] - 1] != nums[i]) {
                // Let nums[nums[i] - 1] = nums[i]
                swap(nums[i], nums[nums[i] - 1]);
            } else {
                i++;
            }
        }

        for (i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                break;
            }
        }

        return i + 1;
    }
};
