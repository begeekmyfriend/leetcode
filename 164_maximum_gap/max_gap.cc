#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2) {
            return 0;
        }

        int min_elem = *min_element(nums.begin(), nums.end());
        int max_elem = *max_element(nums.begin(), nums.end());
        double bucket_size = 1.0 * (max_elem - min_elem) / (nums.size() - 1);
        if (bucket_size == 0) {
            return 0;
        }

        int bucket_cnt = (max_elem - min_elem) / bucket_size + 1;
        vector<int> min_bucket(bucket_cnt, INT_MAX);
        vector<int> max_bucket(bucket_cnt, INT_MIN);
        for (int i = 0; i < nums.size(); i++) {
            int id = (nums[i] - min_elem) / bucket_size;
            min_bucket[id] = min(nums[i], min_bucket[id]);
            max_bucket[id] = max(nums[i], max_bucket[id]);
        }

        int max_gap = 0;
        int last_max = max_bucket[0];
        for (int i = 1; i < bucket_cnt; i++) {
            if (min_bucket[i] != INT_MAX) {
                max_gap = max(min_bucket[i] - last_max, max_gap);
                last_max = max_bucket[i];
            }
        }
        return max_gap;
    }
};
