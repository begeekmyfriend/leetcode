#include <stdio.h>
#include <stdlib.h>

static int binary_search_start(int *a, int size, int target)
{
    int low = -1;
    int high = size;
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > a[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    if (high == size || a[high] != target) {
        return -1;
    } else {
        return high;
    }
}

static int binary_search_end(int *a, int size, int target)
{
    int low = -1;
    int high = size;
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target < a[mid]) {
            high = mid;
        } else {
            low = mid;
        }
    }

    if (low == -1 || a[low] != target) {
        return -1;
    } else {
        return low;
    }
}

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    int *range = malloc(2 * sizeof(int));
    *returnSize = 2;    

    if (numsSize == 0) {
        range[0] = range[1] = -1;
        return range;
    }

    range[0] = binary_search_start(nums, numsSize, target);
    range[1] = binary_search_end(nums, numsSize, target);
    return range;
}

int main(int argc, char **argv)
{
    int i, count;
    int *nums = malloc((argc - 2) * sizeof(int));
    for (i = 0; i < argc - 2; i++) {
        nums[i] = atoi(argv[i + 2]);
    }
    
    int *range = searchRange(nums, argc - 2, atoi(argv[1]), &count);
    printf("%d %d\n", range[0], range[1]);

    return 0;
}
