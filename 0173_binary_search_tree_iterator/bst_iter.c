#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct {
    int size;
    int index;
    int nums[10000];
} BSTIterator;

static void dfs(struct TreeNode* root, BSTIterator *obj)
{
    if (root == NULL) {
        return;
    }

    dfs(root->left, obj);
    obj->nums[obj->size++] = root->val;
    dfs(root->right, obj);
}

static struct BSTIterator *bstIteratorCreate(struct TreeNode *root)
{
    struct BSTIterator *obj = malloc(sizeof(*obj));
    obj->index = 0;
    obj->size = 0;
    dfs(root, obj);
    return iter;
}

/** @return whether we have a next smallest number */
static bool bstIteratorHasNext(struct BSTIterator *obj)
{
    return obj->index < obj->size;
}

/** @return the next smallest number */
static int bstIteratorNext(struct BSTIterator *obj)
{
    return obj->nums[obj->index++];
}

/** Deallocates memory iteriously allocated for the iterator */
static void bstIteratorFree(struct BSTIterator *obj)
{
    free(obj);
}

int main(void)
{
#if 1
    struct TreeNode root;
    root.val = 7;

    struct TreeNode node1[2];
    node1[0].val = 3;
    node1[1].val = 15;

    struct TreeNode node2[4];
    node2[2].val = 9;
    node2[3].val = 20;

    root.left = &node1[0];
    root.right = &node1[1];

    node1[0].left = NULL;
    node1[0].right = NULL;
    node1[1].left = &node2[2];
    node1[1].right = &node2[3];
#else
    struct TreeNode root;
    root.val = 1;

    struct TreeNode node1[2];
    node1[0].val = 2;
    node1[1].val = 3;

    struct TreeNode node2[4];
    node2[0].val = 4;
    node2[3].val = 5;

    root.left = &node1[0];
    root.right = &node1[1];

    node1[0].left = &node2[0];
    node1[0].right = NULL;
    node1[1].left = NULL;
    node1[1].right = &node2[3];
#endif

    node2[0].left = NULL;
    node2[0].right = NULL;
    node2[1].left = NULL;
    node2[1].right = NULL;
    node2[2].left = NULL;
    node2[2].right = NULL;
    node2[3].left = NULL;
    node2[3].right = NULL;

    struct BSTIterator *i = bstIteratorCreate(&root);
    while (bstIteratorHasNext(i)) {
        printf("%d\n", bstIteratorNext(i));
    }
    bstIteratorFree(i);
    return 0;
}
