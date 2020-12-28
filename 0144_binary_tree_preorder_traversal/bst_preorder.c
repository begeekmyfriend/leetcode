#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* preorderTraversal(struct TreeNode* root, int* returnSize)
{
    if (root == NULL) {
        return NULL;
    }

    int cap = 10000, count = 0;
    int *results = malloc(cap * sizeof(int));
    struct TreeNode **stack = malloc(cap / 16 * sizeof(*stack));
    struct TreeNode **top = stack;

    /* root != NULL condition is just for the first iteration and
     * never push NULL into the stack
     */
    while (root != NULL || top != stack) {
        if (root != NULL) {
            results[count++] = root->val;
            /* store the parent node */
            *top++ = root;
            root = root->left;
        } else {
            /* pop up the parent node */
            root = *--top;
            root = root->right;
        }
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
    int *results = preorderTraversal(&root, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");
    return 0;
}
