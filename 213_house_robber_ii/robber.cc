#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        } else {
            return max(rob_(nums.begin() + 1, nums.end()), rob_(nums.begin(), nums.end() - 1));
        }
    }

private:
    int rob_(vector<int>::iterator begin, vector<int>::iterator end) {
        int taken = 0;
        int untaken = 0;
        vector<int>::iterator i;
        for (i = begin; i != end; i++) {
            int tmp_taken = taken;
            taken = untaken + *i;
            untaken = max(untaken, tmp_taken);
        }
        return max(taken, untaken);
    }
};
