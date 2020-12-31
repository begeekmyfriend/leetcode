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
    void recoverTree(TreeNode* root) {
        dfs(root);
        int tmp = p0_->val;
        p0_->val = p1_->val;
        p1_->val = tmp;
    }

private:
    int wrong_ = 0;
    TreeNode *prev_ = nullptr;
    TreeNode *p0_ = nullptr;
    TreeNode *p1_ = nullptr;

    void dfs(TreeNode* root) {
        if (root == nullptr || wrong_ == 2) {
            return;
        }
        
        dfs(root->left);
        if (prev_ != nullptr && prev_->val > root->val) {
            if (++wrong_ == 1) {
                p0_ = prev_;
                // p1 first to be recorded here
                p1_ = root;
            } else if (wrong_ == 2) {
                // update p1 location
                p1_ = root;
            }
        }
        prev_ = root;
        dfs(root->right);
    }
};
