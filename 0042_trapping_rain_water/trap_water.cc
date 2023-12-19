#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        /* In fact if we find the relative higher bar position and then the
         * water level of the position would be determined by the opposite side.
         */
        int res = 0;
        int l = 0, l_max = 0;
        int r = height.size() - 1, r_max = 0;

        while (l < r) {
            // lmax is the highest in height[0...l] and
            // rmax is the highest in height[r...size - 1]
            l_max = max(height[l], l_max);
            r_max = max(height[r], r_max);
            if (l_max < r_max) {
                res += l_max - height[l];
                l++;
            } else {
                res += r_max - height[r];
                r--;
            }
        }

        return res;
    }
};
