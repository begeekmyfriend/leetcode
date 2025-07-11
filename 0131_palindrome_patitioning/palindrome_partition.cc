#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<vector<bool>> isPalindrome(s.size(), vector<bool>(s.size(), true));

        // From bottom to up
        for (int i = s.length() - 1; i >= 0; i--) {
            // From left to right
            for (int j = i + 1; j < s.length(); j++) {
                // notebook for palindrome substring judgement
                isPalindrome[i][j] = s[i] == s[j] && isPalindrome[i + 1][j - 1];
            }
        }

        dfs(s, 0, isPalindrome, res);
        return res;
    }

private:
    vector<string> ans;
    void dfs(const string& s, int start, vector<vector<bool>>& isPalindrome, vector<vector<string>>& res) {
        // DFS for combination. When the start index reaches to the end, all
        // the substrings are collected.
        if (start == s.length()) {
            res.push_back(ans);
            return;
        }

        for (int i = start; i < s.length(); i++) {
            if (isPalindrome[start][i]) {
                ans.push_back(s.substr(start, i - start + 1));
                dfs(s, i + 1, isPalindrome, res);
                ans.pop_back();
            }
        }
    }
};
