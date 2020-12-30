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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++) {
            map_[inorder[i]] = i;
        }
        int size = inorder.size();
        return dfs(inorder, 0, size - 1, postorder, 0, size - 1);
    }

private:
    unordered_map<int, int> map_;
    TreeNode* dfs(vector<int>& inorder, int in_lo, int in_hi, vector<int>& postorder, int post_lo, int post_hi) {
        if (in_lo > in_hi || post_lo > post_hi) {
            return nullptr;
        }
        int value = postorder[post_hi];
        TreeNode *root = new TreeNode(value);
        int index = map_[value];
        root->left = dfs(inorder, in_lo, index - 1, postorder, post_lo, post_lo + (index - in_lo - 1));
        root->right = dfs(inorder, index + 1, in_hi, postorder, post_hi - (in_hi - index), post_hi - 1);
        return root;
    }
};
