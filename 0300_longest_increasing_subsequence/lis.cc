#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> ans;
        for (int x : nums) {
            auto it = lower_bound(ans.begin(), ans.end(), x);
            if (it == ans.end()) {
                ans.push_back(x);
            }
            else *it = x;
        }
        return ans.size();
    }
};
