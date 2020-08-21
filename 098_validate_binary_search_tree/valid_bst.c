#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isValidBST(struct TreeNode* root)
{
    int top = 0;
    int prev = INT_MIN;
    bool first = true;
    struct TreeNode *stack[1000];
    while (top > 0 || root != NULL) {
        if (root != NULL) {
            stack[top++] = root;
            root = root->left;
        } else {
            root = stack[--top];
            if (!first && prev >= root->val) {
                return false;
            }
            first = false;
            prev = root->val;
            root = root->right;
        }
    }
    return true;
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
