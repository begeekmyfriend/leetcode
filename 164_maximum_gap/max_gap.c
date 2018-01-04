#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static inline int gt(int a, int b)
{
    return a > b ? a : b;
}

static inline int lt(int a, int b)
{
    return a < b ? a : b;
}

static int maximumGap(int* nums, int numsSize)
{
    if (numsSize < 2) {
        return 0;
    }

    int i;
    int min = INT_MAX;
    int max = INT_MIN;
    for (i = 0; i < numsSize; i++) {
        min = lt(nums[i], min);
        max = gt(nums[i], max);
    }

    /* the max gap size must be larger than or equal to the average */
    double buck_size = 1.0 * (max - min) / (numsSize - 1);
    /* In case of all elememnts are the same number */
    if (buck_size == 0) {
        return 0;
    }

    int buck_cnt = (max - min) / buck_size + 1;
    int *max_buck = malloc(buck_cnt * sizeof(int));
    int *min_buck = malloc(buck_cnt * sizeof(int));
    for (i = 0; i < buck_cnt; i++) {
        max_buck[i] = INT_MIN;
        min_buck[i] = INT_MAX;
    }

    for (i = 0; i < numsSize; i++) {
        int id = (nums[i] - min) / buck_size;
        max_buck[id] = gt(nums[i], max_buck[id]);
        min_buck[id] = lt(nums[i], min_buck[id]);
    }

    int max_gap = 0;
    /* Must not be empty */
    int last_max = max_buck[0];
    for (i = 1; i < buck_cnt; i++) {
        if (min_buck[i] != INT_MAX) {
            /* What we care about is the difference between the last element
             * in the last max bucket and the first element in the next min
             * bucket since the max gap must be larger or equal than the average
             * while the differences of elements in one bucket must less than
             * the average */
            max_gap = gt(min_buck[i] - last_max, max_gap);
            last_max = max_buck[i];
        }
    }

    return max_gap;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", maximumGap(nums, count));
    return 0;
}
