#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* sliding window pattern 
 * while (r < size) {
 *     // check target condition
 *     while (target_condition) {
 *         // calculate minimum length
 *         // iterate left indicator
 *     }
 *     // iterate right indicator
 * }
 */
static char *minWindow(char *s, char *t)
{
    int i, j, count[256] = { 0 };
    int slen = strlen(s);
    int tlen = strlen(t);
    /* edges of sliding window */
    int l = 0, r = 0;
    int min_len = slen + 1;
    int start = 0;
    int len = 0;

    for (i = 0; i < tlen; i++) {
        count[t[i]]++;
    }

    while (r < slen) {
        if (--count[s[r++]] >= 0) {
            /* pattern found */
            len++;
        }

        while (len >= tlen) {
            if (r - l < min_len) {
                min_len = r - l;
                start = l;
            }

            /* Chars with negative count are not included in the pattern string */
            if (++count[s[l++]] > 0) {
                len--;
            }
        }
    }

    char *result;
    if (min_len <= slen) {
        result = malloc(min_len + 1);
        memcpy(result, s + start, min_len);
        result[min_len] = '\0';
    } else {
        result = "";
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
