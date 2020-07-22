#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int lo = -1;
        int hi = nums.size();
        while (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if (target > nums[mid]) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        return hi;
    }
};
