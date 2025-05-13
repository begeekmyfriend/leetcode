#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // find the first smaller element in decreasing sequence from back to
        // forth.
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // if found, find the first bigger element from back to forth and swap
        // them.
        if (i >= 0) {
            int j = nums.size() - 1;
            while (j >= 0 && nums[i] >= nums[j]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }

        // reverse the subsequence into increasing one.
        reverse(nums.begin() + i + 1, nums.end());
    }
};
