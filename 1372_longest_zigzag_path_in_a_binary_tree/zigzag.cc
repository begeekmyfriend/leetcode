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
    int longestZigZag(TreeNode* root) {
        dfs(root);
        return maxzz - 1;
    }
private:
    int maxzz = 0;
    pair<int, int> dfs(TreeNode *root) {
        if (root == nullptr) {
            return make_pair(0, 0);
        }

        auto subl = dfs(root->left);
        auto subr = dfs(root->right);
        int sublzz = 1 + subl.second;
        int subrzz = 1 + subr.first;
        maxzz = max(maxzz, max(sublzz, subrzz));
        return make_pair(sublzz, subrzz);
    }
};
