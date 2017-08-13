#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode *last = NULL;
static struct TreeNode *m1 = NULL;
static struct TreeNode *m2 = NULL;
static int wrong = 0;

static void traverse(struct TreeNode* node)
{
    if (node->left != NULL) {
        traverse(node->left);
    }

    if (last != NULL && node->val < last->val) {
        if (++wrong == 2) {
            int tmp = node->val;
            node->val = m1->val;
            m1->val = tmp;
        }
        m1 = last;
        m2 = node;
    }
    last = node;

    if (node->right != NULL) {
        traverse(node->right);
    }
}

static void recoverTree(struct TreeNode* root) {
    if (root != NULL) {
        last = NULL;
        m1 = NULL;
        m2 = NULL;
        wrong = 0;
        traverse(root);
        if (wrong == 1) {
            int tmp = m1->val;
            m1->val = m2->val;
            m2->val = tmp;
        }        
    }
}

int main(int argc, char **argv)
{
    struct TreeNode root;
    struct TreeNode left;
    struct TreeNode right;
    root.val = 2;
    root.left = &left;
    root.right = &right;
    left.val = 3;
    left.left = NULL;
    left.right = NULL;
    right.val = 1;
    right.left = NULL;
    right.right = NULL;
    recoverTree(&root);
    printf("%d %d %d\n", root.val, left.val, right.val);
    return 0;
}
