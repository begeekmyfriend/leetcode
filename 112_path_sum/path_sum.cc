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
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == nullptr) {
            // Here is non leaf
            return false;
        } else if (root->left == nullptr && root->right == nullptr && root->val == sum) {
            // Here must be leaf
            return true;
        } else {
            return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
        }
    }
};
