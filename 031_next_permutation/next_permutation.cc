#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() < 2) {
            return;
        }

        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        if (i >= 0) {
            int j = nums.size() - 1;
            while (j >= 0 && nums[j] >= nums[i]) {
                j--;
            }
            swap(nums.begin() + i, nums.begin() + j);
        }

        reverse(nums.begin() + i + 1, nums.end());
    }
};
