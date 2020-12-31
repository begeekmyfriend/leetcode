#include <stdio.h>
#include <stdlib.h>


int coinChange(int* coins, int coinsSize, int amount)
{
    int i, j;
    int *dp = malloc((amount + 1) * sizeof(int));
    for (i = 1; i <= amount; i++) {
        /* INT_MAX */
        dp[i] = amount + 1;
    }

    dp[0] = 0;
    for (i = 1; i <= amount; i++) {
        for (j = 0; j < coinsSize; j++) {
            if (i - coins[j] >= 0) {
                int tmp = 1 + dp[i - coins[j]];
                dp[i] = tmp < dp[i] ? tmp : dp[i];
            }
        }
    }

    return dp[amount] == amount + 1 ? -1 : dp[amount];
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test 11 1 2 5");
        exit(-1);
    }

    int amount = atoi(argv[1]);
    int i, size = argc - 2;
    int *coins = malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        coins[i] = atoi(argv[i + 2]);
    }
    printf("%d\n", coinChange(coins, size, amount));

    return 0;
}
