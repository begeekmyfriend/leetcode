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
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return max_sum;
    }

private:
    int max_sum = INT_MIN;
    int dfs(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int subl = max(0, dfs(root->left));
        int subr = max(0, dfs(root->right));
        int sum = root->val + subl + subr;
        max_sum = max(sum, max_sum);
        return root->val + max(subl, subr);
    }
};
