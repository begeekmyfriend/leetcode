#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode *dfs(struct ListNode **head, int lo, int hi)
{
    if (lo > hi) {
        return NULL;
    }

    int mid = lo + (hi - lo) / 2;
    struct TreeNode *node = malloc(sizeof(*node));
    node->left = dfs(head, lo, mid - 1);
    node->val = (*head)->val;
    (*head) = (*head)->next;
    node->right = dfs(head, mid + 1, hi);
    return node;
}

static struct TreeNode* sortedListToBST(struct ListNode* head)
{
    struct ListNode *p;
    int len = 0;
    for (p = head; p != NULL; p = p->next) {
        len++;
    }
    return dfs(&head, 0, len - 1);
}

int main(int argc, char **argv)
{
    sortedListToBST(NULL);
    return 0;
}
