#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int numDistinct(char* s, char* t)
{
    int s_len = strlen(s);
    int t_len = strlen(t);
    if (t_len == 0 || s_len < t_len) {
        return 0;
    }

    int start = 0;
    while (start < s_len && s[start] != t[0]) {
        start++;
    }
    if (start == s_len) {
        return 0;
    }

    int i, j;
    int *table = malloc((s_len - start) * t_len * sizeof(int));
    int **dp = malloc((s_len - start) * sizeof(int *));
    for (i = 0; i < s_len - start; i++) {
        dp[i] = &table[i * t_len];
    }

    dp[0][0] = 1;
    for (i = 1; i < t_len; i++) {
        dp[0][i] = 0;
    }

    /* I guess it, just dump the dp table and you will find the rule... */
    for (i = 1; i < s_len - start; i++) {
        dp[i][0] = dp[i - 1][0];
        if (s[start + i] == t[0]) {
            dp[i][0]++;
        }
    }

    for (i = 1; i < s_len - start; i++) {
        for (j = 1; j < t_len; j++) {
            dp[i][j] = dp[i - 1][j];
            if (s[start + i] == t[j]) {
                dp[i][j] += dp[i - 1][j - 1]; 
            }
        }
    }

    return dp[s_len - start - 1][t_len - 1];
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test string pattern\n");
        exit(-1);
    }
    printf("%d\n", numDistinct(argv[1], argv[2]));
    return 0;
}
