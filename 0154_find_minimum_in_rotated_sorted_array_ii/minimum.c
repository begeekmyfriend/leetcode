#include <stdio.h>
#include <stdlib.h>

static int findMin(int* nums, int numsSize)
{
    if (numsSize == 1) {
        return nums[0];
    }
    int i, j;
    for (i = 1; i < numsSize; i++) {
        if (nums[i] < nums[i - 1]) {
            return nums[i];
        }
    }
    return nums[0];
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
