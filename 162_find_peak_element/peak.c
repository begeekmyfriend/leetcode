#include <stdio.h>
#include <stdlib.h>

static int findPeakElement(int* nums, int numsSize)
{
    if (numsSize == 1) {
        return nums[0];
    }

    int i;
    for (i = 1; i < numsSize && nums[i] > nums[i - 1]; i++) {}
    return i - 1;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", findPeakElement(nums, count));
    return 0;
}
