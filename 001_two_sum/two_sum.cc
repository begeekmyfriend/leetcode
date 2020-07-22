#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        unordered_map<int, int> ht; 
        for (int i = 0; i < nums.size(); i++) {
            int other = target - nums[i];
            if (ht.find(other) != ht.end()) {
                /* Only one solution for purpose of this problem */
                res.append(ht[other]);
                res.append(i);
                return res;
            }
            ht[nums[i]] = i;
        }
        return res;
    }
};
