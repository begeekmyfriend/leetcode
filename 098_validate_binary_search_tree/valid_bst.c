#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int last_val = -1;

static bool traverse(struct TreeNode* node)
{
    bool ret = true;

    if (ret && node->left != NULL) {
        ret = traverse(node->left);
    }

    if (last_val != -1 && node->val <= last_val) {
        return false;
    }
    last_val = node->val;

    if (ret && node->right != NULL) {
        ret = traverse(node->right);
    }
    return ret;
}

static bool isValidBST(struct TreeNode* root)
{
    if (root == NULL)  return true;
    last_val = -1;
    return traverse(root);
}

int main(int argc, char **argv)
{
    struct TreeNode root;
    struct TreeNode left;
    struct TreeNode right;
    root.val = 2;
    root.left = &left;
    root.right = &right;
    left.val = 1;
    left.left = NULL;
    left.right = NULL;
    right.val = 3;
    right.left = NULL;
    right.right = NULL;
    printf("%s\n", isValidBST(&root) ? "true" : "false");
    return 0;
}
