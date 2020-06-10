#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int maxProduct(int* nums, int numsSize)
{
    int i, maximum = INT_MIN;
    int dp_min = 1;
    int dp_max = 1;
    /* dp records the min or max result of subarray nums[0...i] */
    for (i = 0; i < numsSize; i++) {
        int prev_min = dp_min;
        int prev_max = dp_max;
        dp_min = min(nums[i], min(prev_min * nums[i], prev_max * nums[i]));
        dp_max = max(nums[i], max(prev_min * nums[i], prev_max * nums[i]));
        maximum = max(dp_max, maximum);
    }

    return maximum;
}

int main(int argc, char **argv)
{


    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", maxProduct(nums, count));
    return 0;
}
