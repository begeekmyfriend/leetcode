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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            map_[inorder[i]] = i;
        }
        int size = inorder.size();
        return dfs(preorder, 0, size - 1, inorder, 0, size - 1);
    }

private:
    unordered_map<int, int> map_;
    TreeNode* dfs(vector<int>& preorder, int pre_lo, int pre_hi, vector<int>& inorder, int in_lo, int in_hi) {
        if (pre_lo > pre_hi || in_lo > in_hi) {
            return nullptr;
        }
        int value = preorder[pre_lo];
        TreeNode *root = new TreeNode(value);
        int index = map_[value];
        root->left = dfs(preorder, pre_lo + 1, pre_lo + (index - in_lo), inorder, in_lo, index - 1);
        root->right = dfs(preorder, pre_hi - (in_hi - index) + 1, pre_hi, inorder, index + 1, in_hi);
        return root;
    }
};
