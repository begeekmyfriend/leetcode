#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int findMin(int* nums, int numsSize)
{
    int lo = 0;
    int hi = numsSize - 1;
    int min = INT_MAX;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;        
        min = min < nums[mid] ? min : nums[mid];
        if (nums[mid] > nums[hi]) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return min;
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
