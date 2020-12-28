#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> stack;
        dfs(n, k, 1, stack, res);
        return res;
    }

private:
    void dfs(int n, int k, int start, vector<int>& stack, vector<vector<int>>& res) {
        if (stack.size() == k) {
            res.push_back(stack);
        } else {
            for (int i = start; i <= n; i++) {
                stack.push_back(i);
                dfs(n, k, i + 1, stack, res);
                stack.pop_back();
            }
        }
    }
};
