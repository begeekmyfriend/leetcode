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
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return max_diameter;
    }

private:
    int max_diameter = 0;
    int dfs(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int ld = dfs(root->left);
        int rd = dfs(root->right);
        max_diameter = max(max_diameter, ld + rd);
        return 1 + max(ld, rd);
    }
};
