#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int maxSubArray(int* nums, int numsSize)
{
    int i, max = INT_MIN, len = 0;
    for (i = 0; i < numsSize; i++) {
        len += nums[i];
        /* Calculate maximum each time in loop */
        max = len > max ? len : max;
        if (len < 0) {
            len = 0;
        }
    }
    return max;
}

int main(int argc, char **argv)
{
    int nums[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    printf("%d\n", maxSubArray(nums, sizeof(nums) / sizeof(*nums)));
    return 0;
}
