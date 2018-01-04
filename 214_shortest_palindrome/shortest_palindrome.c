#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static inline char *rev_cpy(char *dst, char *src, int size)
{
    while (size-- > 0) {
        *--dst = *src++;
    }
    return dst;
}

static char *shortestPalindrome(char *s)
{
    int i, j, len = strlen(s);
    char *result = malloc(2 * len + 2);

    strcpy(result, s);
    result[len] = '#';
    rev_cpy(result + 2 * len + 1, s, len);

    int res_len = 2 * len + 1;
    int *next = malloc(res_len * sizeof(int));
    memset(next, 0, res_len * sizeof(int));
    for (i = 1; i < res_len; i++) {
        int j = next[i - 1];
        while (j > 0 && result[i] != result[j]) {
            j = next[j - 1];
        }
        j += result[i] == result[j];
        next[i] = j;
    }

    for (i = 0; i < res_len; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");

    memmove(result, result + len + 1, len + 1);
    int start = len - next[res_len - 1];
    strcpy(result + start, s);
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }

    printf("%s\n", shortestPalindrome(argv[1]));
    return 0;
}
