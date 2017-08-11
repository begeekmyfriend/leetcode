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
    const int NOT_EXISTED   = -1;
    const int NOT_FOUND     =  0;
    memset(m, NOT_EXISTED, sizeof(m));
    memset(f, NOT_EXISTED, sizeof(f));

    /*
     *  Go through t, and inital the m[] and f[]
     *  Notes: a same char can be appeared multiple times.
     */
    for (i = 0; t[i] != '\0'; i++) {
        m[t[i]] == NOT_EXISTED ? m[t[i]] = 1 : m[t[i]]++;
        f[t[i]] = NOT_FOUND;
        pat_len++;
    }

    int start =-1;
    int size = INT_MAX;
    int found = 0;
    int begin = 0;
    for (i = 0; s[i] != '\0'; i++) {
        /* if s[i] is existed in t */
        if (m[s[i]] != NOT_EXISTED) {
            /* if one char has been found enough times, then do not do found++ */
            if (++f[s[i]] <= m[s[i]]) {
                found++;
            }

            if (found >= pat_len) {
                /* 
                 * Find the beginning of the window
                 * 1) f[s[begin]] == NOT_EXISTED  ===> the char at the `begin` is not in t
                 * 2) f[s[begin]] > m[s[begin]]   ===> a same char appeared more than excepted.
                 */
                while (f[s[begin]] == NOT_EXISTED || f[s[begin]] > m[s[begin]]) {
                    if (f[s[begin]] > m[s[begin]]) {
                        f[s[begin]]--;
                    }
                    begin++;
                }

int j;
printf("%d %d\n", begin, i);
for (j = begin; j < i - begin + 1; j++) {
printf("%c", s[j]);
}
printf("\n");
                /* Calculate the minimized window size */
                if (size > i - begin + 1) {
                    start = begin;
                    size = i - begin + 1;
printf("size:%d\n", size);
                }
            }
        }
    }

    char *result = NULL;
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
