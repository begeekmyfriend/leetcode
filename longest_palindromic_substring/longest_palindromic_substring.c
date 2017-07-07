#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char palindrome[1000] = { '\0' };

static void palindrome_find(char *s, int len, int low, int high, int *max_size) {
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

    int max_size = 1;
    for (i = 0; i < len; i++) {
        palindrome_find(s, len, i, i, &max_size);
        palindrome_find(s, len, i, i + 1, &max_size);
    }

    return palindrome;
}

int main(int argc, char **argv) {
    printf("%s\n", longestPalindrom(argv[1]));
    return 0;
}
