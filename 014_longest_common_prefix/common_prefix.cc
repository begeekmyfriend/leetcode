#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string lcp;
        if (strs.empty()) {
            return lcp;
        }
        for (int j = 0; j < strs[0].length(); j++) {
            char c = strs[0][j];
            for (int i = 1; i < strs.size(); i++) {
                if (c != strs[i][j]) {
                    return lcp;
                }
            }
            lcp.push_back(c);
        }
        return lcp;
    }
};
