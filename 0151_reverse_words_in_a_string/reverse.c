#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static reverse(char *s, int lo, int hi)
{
    while (lo < hi) {
        char c = s[lo];
        s[lo] = s[hi];
        s[hi] = c;
        lo++;
        hi--;
    }
}

static void reverseWords(char *s)
{
    int i = 0, j = 0;
    while (s[i] != '\0') {
        while (s[i] == ' ') {
            i++;
        }
        if (s[i] == '\0') break;
        while (s[i] != '\0' && s[i] != ' ') {
            s[j++] = s[i++];
        }
        s[j++] = s[i];
    }
    s[j] = '\0';
    s[--j] = '\0';
    reverse(s, 0, j - 1);

    for (i = 0, j = 0; s[i] != '\0';) {
        for (j = i; s[j] != '\0' && s[j] != ' '; j++) {}
        reverse(s, i, j - 1);
        for (i = j; s[i] != '\0' && s[i] == ' '; i++) {}
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }
    reverseWords(argv[1]);
    printf("%s\n", argv[1]);
    return 0;
}
