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
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            if (root != nullptr) {
                /* Store the parent node */
                stk.push(root);
                root = root->left;
            } else {
                /* Pop up the parent node */
                root = stk.top();
                if (--k == 0) {
                    break;
                }
                stk.pop();
                root = root->right;
            }
        }

        return root->val;
    }
};
