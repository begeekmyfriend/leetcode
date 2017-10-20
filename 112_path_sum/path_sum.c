#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static bool hasPathSum(struct TreeNode *root, int sum)
{
    if (root == NULL) {
        return false;
    } else if (root->left == NULL && root->right == NULL && root->val == sum) {
        return true;
    } else {
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
}

int main(int argc, char **argv)
{
    struct TreeNode root, n1[2], n2[4], n3[8];
    root.val = 5;
    n1[0].val = 4;
    n1[1].val = 8;
    n2[0].val = 11;
    n2[2].val = 13;
    n2[3].val = 4;
    n3[0].val = 7;
    n3[1].val = 2;
    n3[7].val = 1;

    root.left = &n1[0];
    root.right = &n1[1];
    n1[0].left = &n2[0];
    n1[0].right = NULL;
    n1[1].left = &n2[2];
    n1[1].right = &n2[3];
    n2[0].left = &n3[0];
    n2[0].right = &n3[1];
    n2[2].left = NULL;
    n2[2].right = NULL;
    n2[3].left = NULL;
    n2[3].right = &n3[7];
    n3[0].left = NULL;
    n3[0].right = NULL;
    n3[1].left = NULL;
    n3[1].right = NULL;
    n3[7].left = NULL;
    n3[7].right = NULL;

    printf("%s\n", hasPathSum(&root, 22) ? "true" : "false");
    return 0;
}
