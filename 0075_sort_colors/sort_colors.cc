#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            if (nums[i] == 0) {
                i++;
                continue;
            } 
            if (nums[j] != 0) {
                j--;
                continue;
            }
            swap(nums[i], nums[j]);
        }

        j = nums.size() - 1;
        while (i < j) {
            if (nums[i] == 1) {
                i++;
                continue;
            } 
            if (nums[j] != 1) {
                j--;
                continue;
            }
            swap(nums[i], nums[j]);
        }
    }
};
