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

static struct TreeNode *traverse(int *nums, int lo, int hi)
{
    int mid = lo + (hi - lo) / 2;
    struct TreeNode *node = malloc(sizeof(*node));
    node->val = nums[mid];
    node->left = mid > lo ? traverse(nums, lo, mid - 1) : NULL;
    node->right = mid < hi ? traverse(nums, mid + 1, hi) : NULL;
    return node;
}

static struct TreeNode *sortedListToBST(struct ListNode *head)
{
    int i, nums[10000];
    for (i = 0; head != NULL; head = head->next, i++) {
        nums[i] = head->val;
    }
    if (i == 0) {
        return NULL;
    }
    return traverse(nums, 0, i - 1);
}

int main(int argc, char **argv)
{
    sortedListToBST(NULL);
    return 0;
}
