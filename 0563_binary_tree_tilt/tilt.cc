#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int findTilt(TreeNode* root) {
        dfs(root);
        return tilt;
    }

private:
    int tilt = 0;
    int dfs(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int subl = dfs(root->left);
        int subr = dfs(root->right);
        tilt += abs(subl - subr);
        return root->val + subl + subr;
    }
};
