#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() >= 4) {
            vector<int> stack;
            sort(nums.begin(), nums.end());
            k_sum(nums.begin(), nums.end() - 1, target, 4, stack, res);
        }
        return res;
    }

private:
    void k_sum(vector<int>::iterator lo, vector<int>::iterator hi, int target,
               int k, vector<int>& stack, vector<vector<int>>& res) {
        if (k == 2) {
            while (lo < hi) {
                int sum = *lo + *hi;
                if (sum < target) {
                    lo++;
                } else if (sum > target) {
                    hi--;
                } else {
                    stack.push_back(*lo);
                    stack.push_back(*hi);
                    res.push_back(stack);
                    while (++lo < hi && *lo == *(lo - 1)) {}
                    while (lo < hi-- && *hi == *(hi + 1)) {}
                }
            }
        } else {
            for (vector<int>::iterator it = lo; it + k - 1 != hi + 1; it++) {
                if (it > lo && *(it - 1) == *it) { continue; }
                stack.push_back(*it);
                k_sum(it + 1, hi, target - *it, k - 1, stack, res);
                stack.pop_back();
            }
        }
    }
};
