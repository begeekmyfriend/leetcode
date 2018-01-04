#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode *partition(struct TreeNode *node)
{
    if (node == NULL) {
        return NULL;
    }

    if (node->right == NULL && node->left == NULL) {
        return node;
    }

    struct TreeNode *right_last = partition(node->right);
    struct TreeNode *left_last = partition(node->left);

    if (left_last != NULL) {
        left_last->right = node->right;
        node->right = node->left;
        node->left = NULL;
    }

    return right_last != NULL ? right_last : left_last;
}

static void flatten(struct TreeNode *root)
{
    partition(root);
}

int main(void)
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
    n3[6].val = 5;
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
    n2[3].left = &n3[6];
    n2[3].right = &n3[7];
    n3[0].left = NULL;
    n3[0].right = NULL;
    n3[1].left = NULL;
    n3[1].right = NULL;
    n3[6].left = NULL;
    n3[6].right = NULL;
    n3[7].left = NULL;
    n3[7].right = NULL;

    flatten(&root);

    struct TreeNode *p;
    for (p = &root; p != NULL; p = p->right) {
        printf("%d ", p->val);
    }
    printf("\n");
    return 0;
}
