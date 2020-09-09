#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major, count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (count == 0) {
                major = nums[i];
                count++;
            } else if (nums[i] != major) {
                count--;
            } else {
                count++;
            }
        }
        return major;
    }
};
