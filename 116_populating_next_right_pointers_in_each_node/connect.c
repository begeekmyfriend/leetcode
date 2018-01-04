#include <stdio.h>
#include <stdlib.h>

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
};

static void connect(struct TreeLinkNode *root)
{
    if (root == NULL) {
        return;
    }

    struct TreeLinkNode *head = root;
    while (head->left != NULL) {
        struct TreeLinkNode *p;
        for (p = head; p != NULL; p = p->next) {
            p->left->next = p->right;
            p->right->next = p->next == NULL ? NULL : p->next->left;
        }
        head = head->left;
    }
}

int main(int argc, char **argv)
{
    struct TreeLinkNode root, n1[2], n2[4], n3[8];
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
    n1[0].next = NULL;
    n1[1].left = &n2[2];
    n1[1].right = &n2[3];
    n1[1].next = NULL;
    n2[0].left = &n3[0];
    n2[0].right = &n3[1];
    n2[0].next = NULL;
    n2[2].left = NULL;
    n2[2].right = NULL;
    n2[2].next = NULL;
    n2[3].left = &n3[6];
    n2[3].right = &n3[7];
    n2[3].next = NULL;
    n3[0].left = NULL;
    n3[0].right = NULL;
    n3[0].next = NULL;
    n3[1].left = NULL;
    n3[1].right = NULL;
    n3[1].next = NULL;
    n3[6].left = NULL;
    n3[6].right = NULL;
    n3[6].next = NULL;
    n3[7].left = NULL;
    n3[7].right = NULL;
    n3[7].next = NULL;

    connect(&root);
    return 0;
}
