#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct node_backlog {
    struct TreeNode *parent;
    struct TreeNode *right;
};

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
    if (root == NULL) {
        return NULL;
    }

    int cap = 10000, count = 0;
    int *results = malloc(cap * sizeof(int));
    struct node_backlog *stack = malloc(cap / 16 * sizeof(*stack));
    struct node_backlog *top = stack;
    struct TreeNode *node = root;
    struct node_backlog nbl;

    while (node != NULL || top != stack) {
        if (node == NULL) {
            nbl = *--top;
            if (nbl.right != NULL) {
                node = nbl.right;
                nbl.right = NULL;
                *top++ = nbl;
            } else {
                node = nbl.parent;
                results[count++] = node->val;
                node = NULL;
                continue;
            }
        }
        nbl.parent = node;
        nbl.right = node->right;
        *top++ = nbl;
        node = node->left;
    }

    *returnSize = count;
    return results;
}

int main(int argc, char **argv)
{
    struct TreeNode root, node1, node2;
    root.val = 1;
    node1.val = 2;
    node2.val = 3;
    root.left = NULL;
    root.right = &node1;
    node1.left = &node2;
    node1.right = NULL;
    node2.left = NULL;
    node2.right = NULL;

    int i, count = 0;
    int *results = postorderTraversal(&root, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");
    return 0;
}
