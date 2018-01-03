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
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int *table = malloc((len1 + 1) * (len2 + 1) * sizeof(int));
    int **dp = malloc((len1 + 1) * sizeof(int *));
    for (i = 0; i < len1 + 1; i++) {
        dp[i] = table + i * (len2 + 1);
    }

    for (i = 0; i < len2 + 1; i++) {
        dp[0][i] = i;
    }
    for (i = 0; i < len1 + 1; i++) {
        dp[i][0] = i;
    }

    for (i = 1; i < len1 + 1; i++) {
        for (j = 1; j < len2 + 1; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
            }
        }
    }
    return dp[len1][len2];
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
