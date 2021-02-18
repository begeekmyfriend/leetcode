#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static inline int min(int a, int b)
{
    return a < b ? a : b;
}

int minInsertions(char * s){
    int i, j, len = strlen(s);
    int *dp = malloc(len * sizeof(int));
    memset(dp, 0, len * sizeof(int));
    for (i = len - 2; i >= 0; i--) {
        int left_down = 0;
        for (j = i + 1; j < len; j++) {
            int down = dp[j];
            if (s[i] == s[j]) {
                dp[j] = left_down;
            } else {
                dp[j] = min(down, dp[j - 1]) + 1;
            }
            left_down = down;
        }
    }
    return dp[len - 1];
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test s\n");
        exit(-1);
    }

    printf("%d\n", minInsertions(argv[1]));
    return 0;
}
