#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        res.push_back(binary_search_begin(nums, target));
        res.push_back(binary_search_end(nums, target));
        return res;
    }

private:
    int binary_search_begin(vector<int> nums, int target)
    {
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

        if (hi == nums.size() || nums[hi] != target) {
            return -1;
        } else {
            return hi;
        }
    }

    int binary_search_end(vector<int> nums, int target)
    {
        int lo = -1;
        int hi = nums.size();
        while (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if (target < nums[mid]) {
                hi = mid;
            } else {
                lo = mid;
            }
        }

        if (lo == -1 || nums[lo] != target) {
            return -1;
        } else {
            return lo;
        }
    }
};
