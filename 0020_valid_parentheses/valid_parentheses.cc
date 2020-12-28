#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for (int i = 0; i < s.length(); i++) {
            switch(s[i]) {
            case '(':
            case '[':
            case '{':
                stk.push(s[i]);
                break;
            case ')':
                if (stk.empty() || stk.top() != '(') {
                    return false;
                } else {
                    stk.pop();
                    break;
                }
            case ']':
                if (stk.empty() || stk.top() != '[') {
                    return false;
                } else {
                    stk.pop();
                    break;
                }
            case '}':
                if (stk.empty() || stk.top() != '{') {
                    return false;
                } else {
                    stk.pop();
                    break;
                }
            }
        }
        return stk.empty();
    }
};
