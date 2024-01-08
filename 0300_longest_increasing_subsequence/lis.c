#include <stdio.h>
#include <stdlib.h>


static int max(int a, int b)
{
    return a > b ? a : b;
}

static int binary_search(int *nums, int lo, int hi, int target)
{
    while (lo + 1 < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < target) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return hi;
}

int lengthOfLIS(int* nums, int numsSize)
{
#if 0
    int i, piles = 0;
    int *tops = malloc(numsSize * sizeof(int));
    for (i = 0; i < numsSize; i++) {
        int pos = binary_search(tops, -1, piles, nums[i]);
        if (pos == piles) {
            piles++;
        }
        tops[pos] = nums[i];
    }
    return piles;
#else
    int i, j, res = 0;
    int *dp = malloc(numsSize * sizeof(int));

    /* dp array records subsequence length of nums[0...i], so we need to
     * initialize each dp[i] with one element length in the beginning. */
    for (i = 0; i < numsSize; i++) {
        dp[i] = 1;
        for (j = 0; j < i; j++) {
            if (nums[j] > nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    for (i = 0; i < numsSize; i++) {
        res = max(res, dp[i]);
    }

    return res;
#endif
}

int main(int argc, char **argv)
{
    int i;
    int *nums = malloc((argc - 1) * sizeof(int));
    for (i = 0; i < argc - 1; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    printf("%d\n", lengthOfLIS(nums, argc - 1));
    return 0;
}
