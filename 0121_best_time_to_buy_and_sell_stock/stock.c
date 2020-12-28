#include <stdio.h>
#include <stdlib.h>

static int maxProfit(int* prices, int pricesSize)
{
    if (pricesSize == 0) {
        return 0;
    }

    int i, diff = 0, min = prices[0];
    for (i = 1; i < pricesSize; i++) {
        if (prices[i] < min) {
            min = prices[i];
        } else {
            diff = prices[i] - min > diff ? prices[i] - min : diff;
        }
    }

    return diff;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", maxProfit(nums, count));
    return 0;
}
