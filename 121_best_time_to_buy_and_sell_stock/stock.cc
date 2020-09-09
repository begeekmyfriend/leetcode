#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        int diff = 0;
        int minimum = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < minimum) {
                minimum = prices[i];
            } else {
                diff = prices[i] - minimum > diff ? prices[i] - minimum : diff;
            }
        }

        return diff;
    }
};
