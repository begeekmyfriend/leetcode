#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        auto res = dfs(root);
        return max(res.first, res.second);
    }

    pair<int, int> dfs(TreeNode *root) {
        if (root == nullptr) {
            return make_pair(0, 0);
        }
        auto subl = dfs(root->left);
        auto subr = dfs(root->right);
        int taken = root->val + subl.second + subr.second;
        int untaken = max(subl.first, subl.second) + max(subr.first, subr.second);
        return make_pair(taken, untaken);
    }
};
