#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) {
            return 0;
        }

        int max_diff = 0;
        int min_price = prices[0];
        vector<int> left_profits(prices.size());
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < min_price) {
                min_price = prices[i];
            } else {
                int diff = prices[i] - min_price;
                max_diff = max(diff, max_diff);
            }
            left_profits[i] = max_diff;
        }

        int total = 0;
        max_diff = 0;
        int right_profit = 0;
        int max_price = prices[prices.size() - 1];
        for (int i = prices.size() - 2; i >= 0; i--) {
            if (prices[i] > max_price) {
                max_price = prices[i];
            } else {
                int diff = max_price - prices[i];
                right_profit = max(diff, right_profit);
            }
            int profit = left_profits[i] + right_profit;
            total = max(profit, total);
        }

        return total;
    }
};
