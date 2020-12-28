#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int maxDepth(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    int l = maxDepth(root->left) + 1;
    int r = maxDepth(root->right) + 1;
    return l > r ? l : r;
}

int main(void)
{
    printf("%d\n", maxDepth(NULL));
    return 0;
}
