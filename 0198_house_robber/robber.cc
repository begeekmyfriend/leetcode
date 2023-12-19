#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int taken = 0;
        int untaken = 0;
        for (int i = 0; i < nums.size(); i++) {
            int last_taken = taken;
            /* last untaken + nums[i]*/
            taken = untaken + nums[i];
            /* max(last untaken, last taken) */
            untaken = max(untaken, last_taken);
        }
        return max(taken, untaken);
    }
};
