#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static bool dfs(struct TreeNode* node, int min, int max)
{
    if (node == NULL) return true;
    if (node->val < min || node->val > max) return false;
    if (node->left != NULL && node->val == INT_MIN) return false;
    if (node->right != NULL && node->val == INT_MAX) return false;
    return dfs(node->left, min, node->val - 1) && dfs(node->right, node->val + 1, max);
}

static bool isValidBST(struct TreeNode* root)
{
    return dfs(root, INT_MIN, INT_MAX);
}

int main(int argc, char **argv)
{
    struct TreeNode root;
    struct TreeNode left;
    struct TreeNode right;
    root.val = 1;
    root.left = &left;
    root.right = NULL;
    left.val = 1;
    left.left = NULL;
    left.right = NULL;
    right.val = 1;
    right.left = NULL;
    right.right = NULL;
    printf("%s\n", isValidBST(&root) ? "true" : "false");
    return 0;
}
