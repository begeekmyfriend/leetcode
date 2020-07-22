#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        int invalid = -1;
        int len = 0, max_len = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                if (stk.empty()) {
                    invalid = i;
                } else {
                    stk.pop();
                    if (stk.empty()) {
                        /* locate the remote ')' */
                        max_len = max(i - invalid, max_len);
                    } else {
                        /* locate the remote '(' */
                        max_len = max(i - stk.top(), max_len);
                    }
                }
            }
        }

        return max_len;
    }
};
