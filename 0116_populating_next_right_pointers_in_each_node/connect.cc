#include <stdc++.h>

using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }

        if (root->left != nullptr) {
            root->left->next = root->right;
        }
        Node *next = root->next;
        if (root->right != nullptr && next != nullptr) {
            root->right->next = next->left;
        }
        connect(root->left);
        connect(root->right);
        return root;
    }
};
