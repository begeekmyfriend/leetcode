#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int taken = 0;
        int untaken = 0;
        for (int i = 0; i < nums.size(); i++) {
            int tmp_taken = taken;
            taken = untaken + nums[i];
            untaken = max(untaken, tmp_taken);
        }
        return max(taken, untaken);
    }
};
