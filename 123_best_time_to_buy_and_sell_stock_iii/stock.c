#include <stdio.h>
#include <stdlib.h>

static int maxProfit(int* prices, int pricesSize)
{
    if (pricesSize == 0) {
        return 0;
    }

    int i, tmp, diff = 0, min = prices[0];
    int *left_profit = malloc(pricesSize * sizeof(int));
    for (i = 1; i < pricesSize; i++) {
        if (prices[i] < min) {
            min = prices[i];
        } else {
            tmp = prices[i] - min;
            diff = tmp > diff ? tmp : diff;
        }
        left_profit[i] = diff;
    }

    int right_profit = 0;
    int max = prices[pricesSize - 1];
    int total = left_profit[pricesSize - 1];
    for (i = pricesSize - 2; i >= 0; i--) {
        if (prices[i] > max) {
             max = prices[i];
        } else {
            tmp = max - prices[i];
            right_profit = tmp > right_profit ? tmp : right_profit;
        }
        tmp = left_profit[i] + right_profit;
        total = tmp > total ? tmp : total;
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
