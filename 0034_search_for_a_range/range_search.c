#include <stdio.h>
#include <stdlib.h>

static int binary_search_begin(int *a, int size, int target)
{
    int lo = -1;
    int hi = size;
    while (lo + 1 < hi) {
        int mid = lo + (hi - lo) / 2;
        if (target > a[mid]) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    if (hi == size || a[hi] != target) {
        return -1;
    } else {
        return hi;
    }
}

static int binary_search_end(int *a, int size, int target)
{
    int lo = -1;
    int hi = size;
    while (lo + 1 < hi) {
        int mid = lo + (hi - lo) / 2;
        if (target < a[mid]) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    if (lo == -1 || a[lo] != target) {
        return -1;
    } else {
        return lo;
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
    range[0] = binary_search_begin(nums, numsSize, target);
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
