#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int minDepth(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }

    int l = minDepth(root->left) + 1;
    int r = minDepth(root->right) + 1;
    return l < r ? (l > 1 ? l : r) : (r > 1 ? r : l);
}

int main(void)
{
    struct TreeNode root, n1;
    root.val = 1;
    n1.val = 2;
    root.left = &n1;
    root.right = NULL;
    n1.left = NULL;
    n1.right = NULL;
    printf("%d\n", minDepth(&root));
    return 0;
}
