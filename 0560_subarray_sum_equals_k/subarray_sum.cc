#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, sum = 0;
        unordered_map<int, int> pre_sum_cnt;

        // The prefix sum array records the sum of nums[0...i], so we have
        // presum[j] - presum[j] = k when the sum of nums[i...j] equals k.
        // The presum[0] should always be 0. And pre_sum_cnt[0] = 1.
        pre_sum_cnt[0] = 1;
        for (const auto n : nums) {
            // Here the sum means sum of nums[0...j] and the sum0 means sum
            // of nums[0...i] then there will be sum - sum0 = k.
            sum += n;
            int sum0 = sum - k;
            if (ht.count(sum0)) {
                res += pre_sum_cnt[sum0];
            }
            pre_sum_cnt[sum]++;
        }

        return res;
    }
};
