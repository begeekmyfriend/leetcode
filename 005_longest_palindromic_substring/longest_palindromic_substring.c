#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void find(char *s, int len, int low, int high, int *max_size, char *palindrome) {
    while (low >= 0 && high < len && s[low] == s[high]) {
        low--;
        high++;
    }
    low++;
    high--;

    if (high - low + 1 > *max_size) {
        *max_size = high - low + 1;
        memcpy(palindrome, s + low, *max_size);
    }
}

static char *longestPalindrom(char *s) {
    int i;
    if (s == NULL) {
        return NULL;
    }

    int len = strlen(s);
    if (len <= 1) {
        return s;
    }

    char *palindrome = malloc(1000);
    memset(palindrome, 0, sizeof(palindrome));

    int max_size = 0;
    for (i = 0; i < len; i++) {
        /* start from the middle and scan both two sides */
        find(s, len, i, i, &max_size, palindrome);
        find(s, len, i, i + 1, &max_size, palindrome);
    }

    return palindrome;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }
    printf("%s\n", longestPalindrom(argv[1]));
    return 0;
}
