#include <stdio.h>
#include <stdlib.h>

static int maxProfit(int* prices, int pricesSize)
{
    int i, j, diff = 0;
    for (i = 0; i < pricesSize; i++) {
        for (j = i + 1; j < pricesSize; j++) {
            diff = prices[j] - prices[i] > diff ? prices[j] - prices[i] : diff;
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
