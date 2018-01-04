#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static void dfs(struct TreeNode *node, int sum, int *stack, int len, int **results, int *sizes, int *count)
{
    if (node == NULL) {
        return;
    }

    sum -= node->val;
    if (node->left == NULL && node->right == NULL && sum == 0) {
        results[*count] = malloc((len + 1) * sizeof(int));
        memcpy(results[*count], stack, len * sizeof(int));
        results[*count][len] = node->val;
        sizes[*count] = len + 1;
        (*count)++;
        return;
    }
    stack[len] = node->val;
    dfs(node->left, sum, stack, len + 1, results, sizes, count);
    dfs(node->right, sum, stack, len + 1, results, sizes, count);
}

static int **pathSum(struct TreeNode *root, int sum, int **columnSizes, int *returnSize)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int level = 5000, cap = 1000;
    int *stack = malloc(level * sizeof(int));
    int **results = malloc(cap * sizeof(int *));
    *columnSizes = malloc(cap * sizeof(int));
    dfs(root, sum, stack, 0, results, *columnSizes, returnSize);
    return results;
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

    int i, j, count = 0;
    int *sizes;
    int **list = pathSum(&root, 22, &sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }
    return 0;
}
