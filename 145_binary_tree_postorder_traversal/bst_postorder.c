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

static int counting(struct TreeNode* node)
{
    if (node == NULL) {
        return 0;
    }
    return 1 + counting(node->left) + counting(node->right);
}

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
    if (root == NULL) {
        return NULL;
    }

    *returnSize = counting(root);

    int count = 0;
    int *results = malloc(*returnSize * sizeof(int));
    struct node_backlog *stack = malloc(*returnSize * sizeof(*stack));
    struct node_backlog *top = stack;
    struct TreeNode *node = root;

    while (node != NULL || top != stack) {
        if (node == NULL) {
            if ((top - 1)->right != NULL) {
                node = (top - 1)->right;
                (top - 1)->right = NULL;
            } else {
                node = (--top)->parent;
                results[count++] = node->val;
                node = NULL;
                continue;
            }
        }
        top->parent = node;
        top->right = node->right;
        top++;
        node = node->left;
    }

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
