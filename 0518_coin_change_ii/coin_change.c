#include <stdio.h>
#include <stdlib.h>


int change(int amount, int* coins, int coinsSize)
{
    int i, j;
    unsigned int **dp = malloc((coinsSize + 1) * sizeof(unsigned int *));

    for (i = 0; i <= coinsSize; i++) {
        dp[i] = calloc(amount + 1, sizeof(unsigned int));
        dp[i][0] = 1;
    }

    for (i = 1; i <= coinsSize; i++) {
        for (j = 1; j <= amount; j++) {
            if (j - coins[i - 1] >= 0) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[coinsSize][amount];
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
    printf("%d\n", change(amount, coins, size));

    return 0;
}
