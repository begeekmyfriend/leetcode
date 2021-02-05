#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        vector<int> piles;
        sort(envelopes.begin(), envelopes.end(), compare);
        for (const auto& e : envelopes) {
            int pos = binary_search(piles, -1, piles.size(), e[1]);
            if (pos == piles.size()) {
                piles.push_back(e[1]);
            }
            piles[pos] = e[1];
        }
        return piles.size();
    }
private:
    static bool compare(const vector<int>& a, const vector<int>& b) {
        int wa = a[0];
        int wb = b[0];
        int ha = a[1];
        int hb = b[1];
        return wa == wb ? ha > hb : wa < wb;
    }

    int binary_search(vector<int>& nums, int lo, int hi, int target) {
        while (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < target) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        return hi;
    }
};
