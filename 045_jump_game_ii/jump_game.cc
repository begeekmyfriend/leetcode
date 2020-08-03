#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int steps = 0;
        int lo = 0, hi = 0;
        while (hi < nums.size() - 1) {
            int right = 0;
            for (int i = lo; i <= hi; i++) {
                // right > hi for nums[i] > 0 
                right = max(i + nums[i], right);
            }
            // [lo, hi] is the next location range 
            lo = hi + 1;
            hi = right;
            steps++;
        }

        return steps;
    }
};
