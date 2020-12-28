#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int depth(struct TreeNode* root, bool *balance)
{
    if (!(*balance) || root == NULL) {
        return 0;
    }

    int l = depth(root->left, balance) + 1;
    int r = depth(root->right, balance) + 1;
    if (*balance) {
        int diff = l > r ? l - r : r - l;
        *balance = diff < 2;
    }
    return l > r ? l : r;
}

static bool isBalanced(struct TreeNode* root)
{
    bool balance = true;
    depth(root, &balance);
    return balance;
}

int main(void)
{
    struct TreeNode root, n10, n11, n20, n21, n23, n30, n37;
    root.val = 1;
    n10.val = 2;
    n11.val = 3;
    n20.val = 4;
    n21.val = 5;
    n23.val = 6;
    n30.val = 7;
    n37.val = 8;
    root.left = &n10;
    root.right = &n11;
    n10.left = &n20;
    n10.right = &n21;
    n11.left = NULL;
    n11.right = &n23;
    n20.left = &n30;
    n20.right = NULL;
    n21.left = NULL;
    n21.right = NULL;
    n23.left = NULL;
    n23.right = &n37;
    n30.left = NULL;
    n30.right = NULL;
    n37.left = NULL;
    n37.right = NULL;

    printf("%s\n", isBalanced(&root) ? "true" : "false");
    return 0;
}
