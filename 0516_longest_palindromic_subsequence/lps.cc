#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int len = s.length();
        vector<int> dp(len, 1);
        // We have to use level traverse to reduce the dp table size
        for (int i = len - 2; i >= 0; i--) {
            int left_down = 0;
            for (int j = i + 1; j < len; j++) {
                int down = dp[j];
                if (s[i] == s[j]) {
                    dp[j] = left_down + 2;
                } else {
                    dp[j] = max(down, dp[j - 1]);
                }
                left_down = down;
            }
        }
        return dp[len - 1];
    }
};
