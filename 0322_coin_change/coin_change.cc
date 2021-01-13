#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
#if 1
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
#else
        // BFS solution is slow...
        queue<int> q;
        unordered_set<int> visited;
        int step = 0;
        q.push(amount);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                if (q.front() == 0) {
                    return step;
                }
                for (int coin : coins) {
                    int n = q.front() - coin;
                    if (n >= 0) {
                        if (visited.count(n) == 0) {
                            visited.insert(n);
                            q.push(n);
                        }
                    }
                }
                q.pop();
            }
            step++;
        }
        return -1;
#endif
    }
};
