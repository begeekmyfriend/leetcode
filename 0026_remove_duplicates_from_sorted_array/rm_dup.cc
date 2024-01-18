#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[size] != nums[i]) {
                nums[++size] = nums[i];
            }
        }

        return size + 1;
    }
};
