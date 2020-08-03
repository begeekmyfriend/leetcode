#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        // In order to measure the moving size of the sliding window, we
        // need to store the index instead of element into the window.
        vector<int> indexes(nums.size());
        int left = 0, right = 0;
        for (int i = 0; i < nums.size(); i++) {
            while (right > left && nums[i] >= nums[indexes[right - 1]]) {
                right--;
            }
            indexes[right++] = i;
            
            if (i >= k - 1) {
                res.push_back(nums[indexes[left]]);
            }
            
            if (i - indexes[left] + 1 >= k) {
                left++;
            }
        }
        return res;
    }
};
