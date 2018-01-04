#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int partition(struct TreeNode *node, int *max)
{
    int left_max = 0;
    int right_max = 0;

    if (node->left != NULL) {
        left_max = partition(node->left, max);
    }

    if (node->right != NULL) {
        right_max = partition(node->right, max);
    }

    int sum = node->val + left_max + right_max;
    if (sum > *max) {
       *max = sum;
    }

    return node->val + (right_max > left_max ? right_max : left_max);
}

static int maxPathSum(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }

    int max = INT_MIN;
    partition(root, &max);
    return max;
}

int main(void)
{
    struct TreeNode n_1, n_2, n_3, n_4, n_5, n_6, n_7;
    struct TreeNode n0, n1, n2, n3, n4, n5, n6, n7;

    n_7.val = -7;
    n_6.val = -6;
    n_5.val = -5;
    n_4.val = -4;
    n_3.val = -3;
    n_2.val = -2;
    n_1.val = -1;
    n0.val  = 0;
    n1.val  = 1;
    n2.val  = 2;
    n3.val  = 3;
    n4.val  = 4;
    n5.val  = 5;
    n6.val  = 6;
    n7.val  = 7;

    n_7.left  = NULL;
    n_7.right = NULL;
    n_6.left  = &n_7;
    n_6.right = &n_5;
    n_5.left  = NULL;
    n_5.right = NULL;
    n_4.left  = &n_6;
    n_4.right = &n_2;
    n_3.left  = NULL;
    n_3.right = NULL;
    n_2.left  = &n_3;
    n_2.right = &n_1;
    n_1.left  = NULL;
    n_1.right = NULL;
    n0.left   = &n_4;
    n0.right  = &n4;
    n1.left   = NULL;
    n1.right  = NULL;
    n2.left   = &n1;
    n2.right  = &n3;
    n3.left   = NULL;
    n3.right  = NULL;
    n4.left   = &n2;
    n4.right  = &n6;
    n5.left   = NULL;
    n5.right  = NULL;
    n6.left   = &n5;
    n6.right  = &n7;
    n7.left   = NULL;
    n7.right  = NULL;

    printf("%d\n", maxPathSum(&n0));
    return 0;
}
