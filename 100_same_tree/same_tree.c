#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
    if (p != NULL && q != NULL) {
        if (p->val != q->val) {
            return false;
        }
        if (!isSameTree(p->left, q->left)) {
            return false;
        }
        if (!isSameTree(p->right, q->right)) {
            return false;
        }        
    } else {
        return p == q;
    }

    return true;
}

int main(void)
{
    printf("%s\n", isSameTree(NULL, NULL) ? "true" : "false");
    return 0;
}
