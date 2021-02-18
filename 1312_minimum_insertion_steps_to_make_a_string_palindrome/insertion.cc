#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        int len = s.length();
        vector<int> dp(len);
        for (int i = len - 2; i >= 0; i--) {
            int left_down = 0;
            for (int j = i + 1; j < len; j++) {
                int down = dp[j];
                if (s[i] == s[j]) {
                    dp[j] = left_down;
                } else {
                    dp[j] = min(down, dp[j - 1]) + 1;
                }
                left_down = down;
            }
        }
        return dp[len - 1];
    }
};
