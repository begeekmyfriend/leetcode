#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        ser(root, res);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int len = data.length();
        return des(data.c_str(), &len);
    }

private:
    void ser(TreeNode* root, string& res) {
        if (root == nullptr) {
            res.push_back((char) 0x80);
            res.push_back((char) 0x00);
            res.push_back((char) 0x00);
            res.push_back((char) 0x00);
            return;
        }

        ser(root->left, res);
        ser(root->right, res);

        for (int i = sizeof(int) - 1; i >= 0; i--) {
            res.push_back(((char *)&root->val)[i]);
        }
    }
    
    TreeNode* des(const char *data, int *len) {
        if (*len == 0) {
            return nullptr;
        }

        int value;
        const char *s = data + *len - 1;
        for (int i = 0; i < sizeof(int); i++) {
            ((char *)&value)[i] = *s--;
        }
        if (value == INT_MIN) {
            (*len) -= sizeof(int);
            return nullptr;
        }
        (*len) -= sizeof(int);

        TreeNode *root = new TreeNode(value);
        root->right = des(data, len);
        root->left = des(data, len);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
