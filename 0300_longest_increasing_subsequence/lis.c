#include <stdio.h>
#include <stdlib.h>


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

int lengthOfLIS(int* nums, int numsSize){
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
