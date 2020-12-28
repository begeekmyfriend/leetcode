#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        dfs(n, 0, 0, res);
        return res;
    }

private:
    string stack;
    void dfs(int n, int l, int r, vector<string>& res) {
        if (stack.length() == 2 * n) {
            res.push_back(stack);
            return;
        }

        if (l < n) {
            stack.push_back('(');
            dfs(n, l + 1, r, res);
            stack.pop_back();
        }

        if (r < l) {
            stack.push_back(')');
            dfs(n, l, r + 1, res);
            stack.pop_back();
        }
    }
};
