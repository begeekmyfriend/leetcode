#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.length();
        int l2 = text2.length();
        vector<int> dp(l2 + 1);
        int up = 0;
        for (int i = 1; i <= l1; i++) {
            int left_up = 0;
            for (int j = 1; j <= l2; j++) {
                up = dp[j];
                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = left_up + 1;
                } else {
                    dp[j] = max(up, dp[j - 1]);
                }
                left_up = up;
            }
        }
        return dp[l2];
    }
};
