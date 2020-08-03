#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        /* In fact if we find the relative higher bar position and then the
         * water level of the position would be determined by the opposite side.
         */
        int res = 0;
        int left = 0, left_max = 0;
        int right = height.size() - 1, right_max = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] > left_max) {
                    left_max = height[left];
                } else {
                    res += left_max - height[left];
                }
                left++;
            } else {
                if (height[right] > right_max) {
                    right_max = height[right];
                } else {
                    res += right_max - height[right];
                }
                right--;
            }
        }

        return res;
    }
};
