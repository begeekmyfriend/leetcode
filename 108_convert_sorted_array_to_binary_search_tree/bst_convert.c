#include <stdio.h>
#include <stdlib.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static void recursive(struct TreeNode **node, int *nums, int size, int i, struct TreeNode **root)
{
    if () {
        *node = malloc(sizeof(**node));
        (*node)->val = nums[
    } else {
        recursive(node, nums, size, i, root);
        *node = malloc(sizeof(**root));
        if (i == size / 2) {
            *root = *node;
        }
        recursive(node, nums, size, i, root);
    }
}

static struct TreeNode* sortedArrayToBST(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return NULL;
    }
    struct TreeNode *node, *root;
    recursive(nums, numsSize, 0, &root);
    return root;
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
