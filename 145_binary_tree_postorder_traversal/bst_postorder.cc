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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<pair<TreeNode *, TreeNode *>> stk;
        while (!stk.empty() || root != nullptr) {
            if (root != nullptr) {
                stk.push(make_pair(root, root->right));
                root = root->left;
            } else {
                if (stk.top().second != nullptr) {
                    // Into right
                    root = stk.top().second;
                    stk.top().second = nullptr;
                } else {
                    // True backtracing
                    res.push_back(stk.top().first->val);
                    stk.pop();
                    root = nullptr;
                }
            }
        }
        return res;
    }
};
