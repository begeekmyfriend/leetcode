#include <stdio.h>
#include <stdlib.h>

static int searchInsert(int* nums, int numsSize, int target)
{
    int low = -1;
    int high = numsSize;
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }
    return high;
}

int main(int argc, char **argv)
{
    int i;
    int *nums = malloc((argc - 2) * sizeof(int));
    for (i = 0; i < argc - 2; i++) {
        nums[i] = atoi(argv[i + 2]);
    }
    printf("%d\n", searchInsert(nums, argc - 2, atoi(argv[1])));
    return 0;
}
