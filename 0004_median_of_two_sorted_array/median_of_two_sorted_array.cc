#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int sum = nums1.size() + nums2.size();
        vector<int> nums;
        int i = 0, j = 0, k;
        int half = sum / 2 + 1;
        for (k = 0; k < half; k++) {
            int n;
            if (i < nums1.size() && j < nums2.size()) {
                n = (nums1[i] < nums2[j]) ? nums1[i++] : nums2[j++];
            } else if (i < nums1.size()) {
                n = nums1[i++];
            } else if (j < nums2.size()) {
                n = nums2[j++];
            }
            nums.push_back(n);
        }

        if (sum % 2) {
            return nums[k-1];
        } else {
            return (nums[k-1] + nums[k-2]) / 2.0;
        }
    }
};
