#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *minWindow(char *s, char *t)
{
    int i, j, count[256] = { 0 };
    int slen = strlen(s);
    int tlen = strlen(t);
    for (i = 0; i < tlen; i++) {
        count[t[i]]++;
    }

    /* edges of sliding window */
    int lo = 0, hi = 0;
    int min_len = slen + 1;
    int start = 0;
    int chars_to_meet = tlen;
    while (hi < slen) {
        if (--count[s[hi++]] >= 0) {
            /* pattern found */
            chars_to_meet--;
        }

        while (chars_to_meet == 0) {
            if (hi - lo < min_len) {
                min_len = hi - lo;
                start = lo;
            }

            /* Chars with negative count are not included in the pattern string */
            if (++count[s[lo++]] > 0) {
                /* chars_to_meet == 1 */
                chars_to_meet++;
            }
        }
    }

    char *result;
    if (min_len <= slen) {
        result = malloc(min_len + 1);
        memcpy(result, s + start, min_len);
        result[min_len] = '\0';
    } else {
        result = malloc(1);
        result[0] = '\0';
    }

    return result;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test string pattern\n");
        exit(-1);
    }
    printf("Answer: %s\n", minWindow(argv[1], argv[2]));
    return 0;
}
