#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int maxProfit(int* prices, int pricesSize)
{
    int i, j, total = 0;
    for (i = 1; i < pricesSize; i++) {
        total += prices[i] > prices[i - 1] ? prices[i] - prices[i - 1] : 0;
    }
    return total;
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
