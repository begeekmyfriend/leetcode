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
    int count = 0;
    int *results = malloc(100 * sizeof(int));
    struct node_backlog *stack = malloc(100 * sizeof(*stack));
    struct node_backlog *top = stack;

    /* root != NULL condition is just for the first iteration and
     * never push NULL into the stack
     */
    while (root != NULL || top != stack) {
        if (root != NULL) {
            /* push both parent and its right child */
            top->parent = root;
            top->right = root->right;
            top++;
            root = root->left;
        } else {
            if ((top - 1)->right != NULL) {
                /* switch to right child but not pop up the parent */
                root = (top - 1)->right;
                /* avoid infinite loop */
                (top - 1)->right = NULL;
            } else {
                root = (--top)->parent;
                results[count++] = root->val;
                /* we need to backtrace */
                root = NULL;
            }
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
    int *results = postorderTraversal(&root, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");
    return 0;
}
