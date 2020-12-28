#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static void dfs(struct TreeNode *node, struct TreeNode **prev,
                struct TreeNode **p1, struct TreeNode **p2, int *wrong)
{
    if (node == NULL || *wrong == 2) {
        return;
    }

    dfs(node->left, prev, p1, p2, wrong);

    /* We must use pointer to pointer for previous object in recursion */
    if (*prev != NULL && node->val < (*prev)->val) {
        (*wrong)++;
        if (*wrong == 1) {
            *p1 = *prev;
            /* p2 should be recorded here in some cases */
            *p2 = node;
        } else if (*wrong == 2) {
            *p2 = node;
        }
    }
    *prev = node;

    dfs(node->right, prev, p1, p2, wrong);
}

static void recoverTree(struct TreeNode* root)
{
    int wrong = 0;
    struct TreeNode *prev = NULL;
    struct TreeNode *p1 = NULL;
    struct TreeNode *p2 = NULL;
    dfs(root, &prev, &p1, &p2, &wrong);
    int tmp = p1->val;
    p1->val = p2->val;
    p2->val = tmp;
}

int main(int argc, char **argv)
{
    struct TreeNode root;
    struct TreeNode left;
    struct TreeNode right;
    root.val = 2;
    root.left = &left;
    root.right = &right;
    left.val = 3;
    left.left = NULL;
    left.right = NULL;
    right.val = 1;
    right.left = NULL;
    right.right = NULL;
    recoverTree(&root);
    printf("%d %d %d\n", root.val, left.val, right.val);
    return 0;
}
