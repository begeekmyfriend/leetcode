#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int dfs(struct TreeNode* node, int sum)
{
    int total = 0;
    sum = sum * 10 + node->val;

    if (node->left == NULL && node->right == NULL) {
        return sum;
    } else {
        if (node->left != NULL) {
            total += dfs(node->left, sum);
        }
        if (node->right != NULL) {
            total += dfs(node->right, sum);
        }
        return total;
    }
}

static int sumNumbers(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    return dfs(root, 0);
}

int main(void)
{
    struct TreeNode root, n10, n11, n20, n21, n22, n23;
    root.val = 1;
    n10.val = 2;
    n11.val = 2;
    n20.val = 3;
    n21.val = 4;
    n22.val = 4;
    n23.val = 3;
    root.left = &n10;
    root.right = &n11;
    n10.left = &n20;
    n10.right = &n21;
    n11.left = &n22;
    n11.right = &n23;
    n20.left = NULL;
    n20.right = NULL;
    n21.left = NULL;
    n21.right = NULL;
    n22.left = NULL;
    n22.right = NULL;
    n23.left = NULL;
    n23.right = NULL;
    printf("%d\n", sumNumbers(&root));
    return 0;
}
