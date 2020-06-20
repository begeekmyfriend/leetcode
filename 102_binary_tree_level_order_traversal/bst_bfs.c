#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BST_MAX_LEVEL 800

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static void bfs(struct TreeNode *root, int **results, int *count, int *col_sizes, int *size, int level)
{
    if (root == NULL) {
        return;
    }

    *count = level + 1 > *count ? level + 1 : *count;
    if (col_sizes[level] == 0) {
        *size = *size > 256 ? 256 : *size * 2;
        results[level] = malloc(*size * sizeof(int));
    }
    results[level][col_sizes[level]++] = root->val;
    bfs(root->left, results, count, col_sizes, size, level + 1);
    bfs(root->right, results, count, col_sizes, size, level + 1);
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *returnColumnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
static int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int size = 1;
    *returnSize = 0;
    int **results = malloc(BST_MAX_LEVEL * sizeof(int *));
    *returnColumnSizes = malloc(BST_MAX_LEVEL * sizeof(int));
    memset(*returnColumnSizes, 0, BST_MAX_LEVEL * sizeof(int));
    bfs(root, results, returnSize, *returnColumnSizes, &size, 0);
    return results;
}

int main(void)
{
    struct TreeNode root;
    root.val = 3;

    struct TreeNode node1[2];
    node1[0].val = 9;
    node1[1].val = 20;

    struct TreeNode node2[4];
    node2[2].val = 15;
    node2[3].val = 7;

    root.left = &node1[0];
    root.right = &node1[1];

    node1[0].left = NULL;
    node1[0].right = NULL;
    node1[1].left = &node2[2];
    node1[1].right = &node2[3];

    node2[0].left = NULL;
    node2[0].right = NULL;
    node2[1].left = NULL;
    node2[1].right = NULL;
    node2[2].left = NULL;
    node2[2].right = NULL;
    node2[3].left = NULL;
    node2[3].right = NULL;

    int i, j, count = 0, *col_sizes;
    int **lists = levelOrder(&root, &count, &col_sizes);
    for (i = 0; i < count; i++) {
        for (j = 0; j < col_sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}
