#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int i;
        for (i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) {
                break;
            }
        }
        return i - 1;
    }
};
