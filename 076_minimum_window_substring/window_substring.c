#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static char *minWindow(char *s, char *t)
{
    /*
     * Declare two "hash map" for ASCII chars
     * f[]: represents the char found in s
     * m[]: stores the chars in t
     */
    int i, f[256], m[256], pat_len = 0;
    memset(m, 0, sizeof(m));
    memset(f, 0, sizeof(f));

    /*
     *  Go through t, and inital the m[] and f[]
     *  Notes: duplicate char is allowed.
     */
    for (i = 0; t[i] != '\0'; i++) {
        m[t[i]]++;
        pat_len++;
    }

    int start =-1;
    int size = INT_MAX;
    int found = 0;
    int begin = 0;
    for (i = 0; s[i] != '\0'; i++) {
        /* First, find the right side of the window which should be in t */
        if (m[s[i]] > 0) {
            /* if one char has been found enough times, then do not do found++ */
            if (++f[s[i]] <= m[s[i]]) {
                found++;
            }

            /* the right side of the window is confirmed as i */
            /* The found counter will no more increase if the first right side of the window is confirmed,
             * the next step run here can also be regarded as a new right side of a new window. */
            if (found == pat_len) {
                /* Then we need to find the left side of the window
                 * 1) m[s[begin]] == 0 => Both left and right side should be found in t
                 * 2) f[s[begin]] > m[s[begin]] => duplicate chars are more than excepted in the window so that we can even shrink the size. */
                while (m[s[begin]] == 0 || f[s[begin]] > m[s[begin]]) {
                    if (f[s[begin]] > m[s[begin]]) {
                        f[s[begin]]--;
                    }
                    begin++;
                }

                /* Calculate the minimized window size */
                if (size > i - begin + 1) {
                    start = begin;
                    size = i - begin + 1;
                }
            }
        }
    }

    char *result;
    if (start >= 0 && size > 0) {
        result = malloc(size + 1);
        memcpy(result, s + start, size);
        result[size] = '\0';
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
