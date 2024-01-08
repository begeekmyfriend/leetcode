#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 *        word1="abb", word2="abccb"
 *
 *        1) Initialize the DP matrix as below:
 *
 *               "" a b c c b
 *            "" 0  1 2 3 4 5
 *            a  1
 *            b  2
 *            b  3
 *
 *        2) Dynamic Programming
 *
 *               "" a b c c b
 *            ""  0 1 2 3 4 5
 *            a   1 0 1 2 3 4 
 *            b   2 1 0 1 2 3
 *            b   3 2 1 1 2 2
 */ 

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static int minDistance(char* word1, char* word2)
{
    int i, j;
    int l1 = strlen(word1);
    int l2 = strlen(word2);
    int *table = malloc((l1 + 1) * (l2 + 1) * sizeof(int));
    int **dp = malloc((l1 + 1) * sizeof(int *));

    for (i = 0; i < l1 + 1; i++) {
        dp[i] = table + i * (l2 + 1);
    }

    dp[0][0] = 0;
    for (i = 1; i <= l2; i++) {
        dp[0][i] = i;
    }
    for (i = 1; i <= l1; i++) {
        dp[i][0] = i;
    }

    for (i = 1; i <= l1; i++) {
        for (j = 1; j <= l2; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
            }
        }
    }

    return dp[l1][l2];
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test word1 word2\n");
        exit(-1);
    }
    printf("%d\n", minDistance(argv[1], argv[2]));
    return 0;
}
