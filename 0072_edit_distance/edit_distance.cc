#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int l1 = word1.length();
        int l2 = word2.length();
        vector<int> dp(l2 + 1);
        for (int i = 0; i <= l2; i++) {
            dp[i] = i;
        }

        int up = 0;
        for (int i = 1; i <= l1; i++) {
            int left_up = dp[0];
            dp[0] = i;
            for (int j = 1; j <= l2; j++) {
                 up = dp[j];
                 if (word1[i - 1] == word2[j - 1]) {
                     dp[j] = left_up;
                 } else {
                     dp[j] = 1 + min(left_up, min(up, dp[j - 1]));
                 }
                 left_up = up;
            }
        }
        return dp[l2];
    }
};
