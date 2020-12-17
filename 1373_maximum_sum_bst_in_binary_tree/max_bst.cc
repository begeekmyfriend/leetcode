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
    int maxSumBST(TreeNode* root) {
        dfs(root);
        return max(0, max_sum);
    }
private:
    struct TreeInfo {
        bool isBst;
        int min_val;
        int max_val;
        int sum_val;
        TreeInfo() : isBst(true), min_val(INT_MAX), max_val(INT_MIN), sum_val(0) {}
        TreeInfo(bool bst, int min, int max, int sum) : isBst(bst), min_val(min), max_val(max), sum_val(sum) {}
    };

    int max_sum = INT_MIN;
    TreeInfo *dfs(TreeNode *root) {
        if (root == nullptr) {
            return new TreeInfo();
        }

        auto subl = dfs(root->left);
        auto subr = dfs(root->right);

        int sum = root->val + subl->sum_val + subr->sum_val;
        if (subl->isBst && subr->isBst && root->val > subl->max_val && root->val < subr->min_val) {
            max_sum = max(sum, max_sum);
            // For leaf nodes
            int min_val = min(root->val, subl->min_val);
            int max_val = max(root->val, subr->max_val);
            return new TreeInfo(true, min_val, max_val, sum);
        } else {
            return new TreeInfo(false, INT_MAX, INT_MIN, sum);
        }
    }
};
