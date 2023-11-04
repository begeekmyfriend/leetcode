#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int findMin(int* nums, int numsSize)
{
    int lo = 0;
    int hi = numsSize - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;        
        if (nums[mid] < nums[hi]) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return nums[lo];
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", findMin(nums, count));
    return 0;
}
