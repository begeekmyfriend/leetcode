#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    /* recursive version too slow thanks to substr() */
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= p.length(); i++) {
            dp[0][i] = p[0][i - 1] == '*' && i >= 2 && dp[0][i - 2];
        }

        for (int i = 1; i <= s.length(); i++) {
            for (int j = 1; j <= p.length(); j++) {
                bool match;
                if (j >= 2 && p[j - 1] == '*') {
                    match = (s[i - 1] == p[j - 2] || p[j - 2] == '.');
                    dp[i][j] = dp[i][j - 2] || (match && dp[i - 1][j]);
                } else {
                    match = (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                    dp[i][j] = match && dp[i - 1][j - 1];
                }
            }
        }

        return dp[s.size()][p.size()];
    }
};
