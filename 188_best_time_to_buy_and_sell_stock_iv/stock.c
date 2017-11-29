#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int maxProfit(int k, int* prices, int pricesSize)
{
    if (pricesSize == 0) {
        return 0;
    }

    int i, j;
    if (k > pricesSize / 2) {
        /* We can make transactions as many as we can */
        int total = 0;
        for (i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                total += prices[i] - prices[i - 1];
            }
        }
        return total;
    } else {
#if 1
        /* DP solution - O(kn) complexity
         * dp[i, j] = max (dp[i, j-1], // same times transactions, but one days before.
         *                 dp[i-1, t] + prices[j] - prices[t+1])  // for all of (0 <= t < j )
         *                                                        // this means find max profit from previous any of days
         */
        int **dp = malloc((k + 1) * sizeof(int *));
        for (i = 0; i <= k; i++) {
            dp[i] = malloc((pricesSize + 1) * sizeof(int));
            memset(dp[i], 0, (pricesSize + 1) * sizeof(int));
        }

        for (i = 1; i <= k; i++) {
//printf("i:%d\n", i);
//printf("\tprev_profit = %d - %d\n", dp[i - 1][0], prices[0]);
            int prev_profit = dp[i - 1][0] - prices[0];
            for (j = 1; j <= pricesSize; j++) {
//printf("\tj:%d\n", j);
                dp[i][j] = max(dp[i][j - 1], prev_profit + prices[j - 1]); /* prices[j - 1] means sell on Day j for dp[i][j] */
//printf("\tdp[%d][%d] = max(%d, %d + %d)\n", i, j, dp[i][j - 1], prev_profit, prices[j - 1]);
                if (j < pricesSize) {
//printf("\tprev_profit = max(%d, %d - %d)\n", prev_profit, dp[i - 1][j], prices[j]);
                    prev_profit = max(prev_profit, dp[i - 1][j] - prices[j]);
                }
            }
        }
#if 0
        printf("  ");
        for (i = 0; i < pricesSize; i++) {
            printf("%d ", prices[i]);
        }
        printf("\n");
        for (i = 0; i <= k; i++) {
            for (j = 0; j <= pricesSize; j++) {
                printf("%d ", dp[i][j]);
            }
            printf("\n");
        }
#endif

        return dp[k][pricesSize];
#else
        /* local[i][j] j transactions at most and the last max profix until Day i */
        int *local = malloc((k + 1) * sizeof(int));
        /* global[i][j] j transactions at most until Day i */
        int *global = malloc((k + 1) * sizeof(int));
        memset(local, 0, (k + 1) * sizeof(int));
        memset(global, 0, (k + 1) * sizeof(int));
        for (i = 0; i < pricesSize - 1; i++) {
            int diff = prices[i + 1] - prices[i];
            for (j = k; j >= 1; j--) {
                int tmp1 = global[j - 1] + (diff > 0 ? diff : 0);
                int tmp2 = local[j] + diff;
                local[j] = tmp1 > tmp2 ? tmp1 : tmp2;
                global[j] = global[j] > local[j] ? global[j] : local[j];
            }
        }
        return global[k];
#endif
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test k n1 n2...\n");
        exit(-1);
    }

    int i, count = argc - 2;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 2]);
    }
    printf("%d\n", maxProfit(atoi(argv[1]), nums, count));
    return 0;
}
