#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if 0
int minCut(char *s)
{
    int len = strlen(s);
    if (len <= 1) {
        return 0;
    }

    int i, j;
    bool **isPal = malloc(len * sizeof(bool *));
    for (i = 0; i < len; i++) {
        isPal[i] = malloc(len);
        memset(isPal[i], false, len);
    }

    for (i = len - 1; i >= 0; i--) {
        for(j = i; j < len; j++) {
            if ((i + 1 > j - 1 || isPal[i + 1][j - 1]) && s[i] == s[j]) {
                isPal[i][j] = true;
            }
        }
    }

    int *cuts = malloc((len + 1) * sizeof(int));
    for (i = 0; i <= len; i++) {
        cuts[i] = i - 1;
    }

    for (i = 1; i <= len; i++) {
        for (j = i - 1; j >= 0; j--) {
            if (isPal[j][i - 1]) {
                if (cuts[j] + 1 < cuts[i]) {
                    cuts[i] = cuts[j] + 1;
                }
            }
        }
    }

    return cuts[len];
}
#endif

static int minCut(char* s)
{
    int len = strlen(s);
    if (len <= 1) {
        return 0;
    }

    int i, j;
    int *cuts = malloc((len + 1) * sizeof(int));
    for (i = 0; i <= len; i++) {
        cuts[i] = i - 1;
    }

    for (i = 0; i < len; i++) {
        /* odd length palindrome */
        for (j = 0; i - j >= 0 && i + j < len && s[i - j] == s[i + j]; j++) {
            if (cuts[i - j] + 1 < cuts[i + j + 1]) {
                cuts[i + j + 1] = cuts[i - j] + 1;
            }
        }

        /* even length palindrome */
        for (j = 1; i - j + 1 >= 0 && i + j < len && s[i - j + 1] == s[i + j]; j++) {
            if (cuts[i - j + 1] + 1 < cuts[i + j + 1]) {
                cuts[i + j + 1] = cuts[i - j + 1] + 1;
            }
        }
    }

    return cuts[len];
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }

    printf("%d\n", minCut(argv[1]));
    return 0;
}
