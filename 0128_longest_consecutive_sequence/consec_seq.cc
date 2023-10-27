#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        unordered_set<int> s;
        for (int i = 0; i < nums.size(); i++) {
            s.insert(nums[i]);
        }
        for (int n : nums) {
            if (!s.count(n - 1)) {
                int len = 0;
                int num = n;
                while (s.count(num)) {
                    s.erase(num);
                    num++;
                    len++;
                }
                res = len > res ? len : res;
            }
        }
        return res;
    }
};
