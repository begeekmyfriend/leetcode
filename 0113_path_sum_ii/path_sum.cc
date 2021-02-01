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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> res;
        dfs(root, targetSum, res);
        return res;
    }
private:
    vector<int> stack;
    void dfs(TreeNode* root, int sum, vector<vector<int>>& res) {
        if (root == nullptr) {
            return;
        } else if (root->left == nullptr && root->right == nullptr && sum == root->val) {
            stack.push_back(root->val);
            res.push_back(stack);
            stack.pop_back();
        } else {
            stack.push_back(root->val);
            dfs(root->left, sum - root->val, res);
            dfs(root->right, sum - root->val, res);
            stack.pop_back();
        }
    }
};
