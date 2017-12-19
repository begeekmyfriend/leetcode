#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int _rob(int* nums, int numsSize)
{
    int i;
    int **money = malloc((numsSize + 1) * sizeof(int *));
    for (i = 0; i < numsSize + 1; i++) {
        money[i] = malloc(2 * sizeof(int));
        memset(money[i], 0, 2 * sizeof(int));
    }

    for (i = 1; i <= numsSize; i++) {
        int cash = nums[i - 1];
        money[i][0] = max(money[i - 1][0], money[i - 1][1]);
        money[i][1] = money[i - 1][0] + cash;
    }

    return max(money[numsSize][0], money[numsSize][1]);
}

static int rob(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return 0;
    } else if (numsSize == 1) {
        return nums[0];
    } else {
        return max(_rob(nums + 1, numsSize - 1), _rob(nums, numsSize - 1));
    }
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", rob(nums, count));
    return 0;
}
