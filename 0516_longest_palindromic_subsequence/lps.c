#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static inline int max(int a, int b)
{
    return a > b ? a : b;
}

int longestPalindromeSubseq(char * s)
{
    int i, j, k;
    int len = strlen(s);
    int **dp = malloc(len * sizeof(int *));
    for (i = 0; i < len; i++) {
        dp[i] = malloc(len * sizeof(int));
        memset(dp[i], 0, len * sizeof(int));
        dp[i][i] = 1;
    }

    for (k = 1; k < len; k++) {
        for (i = 0; i < len - k; i++) {
            j = i + k;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
            }
        }
    }
    return dp[0][len - 1];
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test s\n");
        exit(-1);
    }

    printf("%d\n", longestPalindromeSubseq(argv[1]));
    return 0;
}
