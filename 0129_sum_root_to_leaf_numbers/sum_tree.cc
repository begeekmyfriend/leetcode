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
    int sumNumbers(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return dfs(root, 0);
    }
private:
    int dfs(TreeNode *root, int sum) {
        // Here we have to use pre-order.
        // sum must be in argument stack of recusion.
        sum = sum * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            return sum;
        } else {
            int total = 0;
            if (root->left != nullptr) {
                total += dfs(root->left, sum);
            }
            if (root->right != nullptr) {
                total += dfs(root->right, sum);
            }
            return total;
        }
    }
};
