#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int partition(int *nums, int lo, int hi)
{
    if (lo == hi) {
        return nums[lo];
    }

    int ce = (hi - lo) / 2;
    int left_max = partition(nums, lo, lo + ce);
    int right_max = partition(nums, hi - ce, hi);

    int i;
    int left_border = 0, left_border_max = INT_MIN;
    for (i = ce; i >= lo; i--) {
        left_border += nums[i];
        if (left_border > left_border_max) {
            left_border_max = left_border;
        }
    }

    int right_border = 0, right_border_max = INT_MIN;
    for (i = ce + 1; i <= hi; i++) {
        right_border += nums[i];
        if (right_border > right_border_max) {
            right_border_max = right_border;
        }
    }

    int sum = left_border_max + right_border_max;
    int max = left_max > right_max ? left_max : right_max;
    return sum > max ? sum : max;
}

static int maxSubArray(int* nums, int numsSize)
{
#if 1
    int i, len = 0, max = INT_MIN;
    for (i = 0; i < numsSize; i++) {
        len += nums[i];
        /* Calculate maximum each time in loop */
        max = len > max ? len : max;
        if (len < 0) {
            len = 0;
        }
    }
    return max;
#else
    return partition(nums, 0, numsSize - 1);
#endif
}

int main(int argc, char **argv)
{
    int nums[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    printf("%d\n", maxSubArray(nums, sizeof(nums) / sizeof(*nums)));
    return 0;
}
