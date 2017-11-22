#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

struct BSTIterator {
    struct ListNode dummy;
    struct ListNode *p;
};

static void bst_iter_generater(struct TreeNode *node, struct BSTIterator *iter)
{
    if (node->left != NULL) {
        bst_iter_generater(node->left, iter);
    }

    struct ListNode *new = malloc(sizeof(*new));
    new->val = node->val;
    new->next = NULL;
    if (iter->p != NULL) {
        iter->p->next = new;
    } else {
        iter->dummy.next = new;
    }
    iter->p = new;

    if (node->right != NULL) {
        bst_iter_generater(node->right, iter);
    }
}

static struct BSTIterator *bstIteratorCreate(struct TreeNode *root)
{
    struct BSTIterator *iter = malloc(sizeof(*iter));
    if (root != NULL) {
        iter->p = NULL;
        bst_iter_generater(root, iter);
    }
    iter->p = &iter->dummy;
    return iter;
}

/** @return whether we have a next smallest number */
static bool bstIteratorHasNext(struct BSTIterator *iter)
{
    return iter->p->next != NULL;
}

/** @return the next smallest number */
static int bstIteratorNext(struct BSTIterator *iter)
{
    iter->p = iter->p->next;
    return iter->p->val;
}

/** Deallocates memory iteriously allocated for the iterator */
static void bstIteratorFree(struct BSTIterator *iter)
{
    iter->p = iter->dummy.next;
    while (iter->p != NULL) {
        iter->dummy.next = iter->p->next;
        free(iter->p);
        iter->p = iter->dummy.next;
    }
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
