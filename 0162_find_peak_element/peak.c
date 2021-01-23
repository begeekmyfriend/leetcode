#include <stdio.h>
#include <stdlib.h>


int findPeakElement(int* nums, int numsSize)
{
    int i;
    for (i = 1; i < numsSize; i++) {
        if (nums[i] < nums[i - 1]) {
            break;
        }
    }
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
