#include <stdio.h>
#include <stdlib.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode *partition(int *nums, int lo, int hi)
{
    int mid = lo + (hi - lo) / 2;
    struct TreeNode *node = malloc(sizeof(*node));
    node->val = nums[mid];
    node->left = mid > lo ? partition(nums, lo, mid - 1) : NULL;
    node->right = mid < hi ? partition(nums, mid + 1, hi) : NULL;
    return node;
}

static struct TreeNode* sortedArrayToBST(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return NULL;
    }
    return partition(nums, 0, numsSize - 1);
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    sortedArrayToBST(nums, count);
    return 0;
}
