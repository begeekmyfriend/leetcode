#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* The recursive way is quite simple.
 *    1) break the string to two parts: 
 *          s1[0..j]   s1[j+1..n]
 *          s2[0..j]   s2[j+1..n]
 *    2) then
 *          isScramble(s1[0..j], s2[0..j]) &&  isScramble(s1[j+1..n], s2[j+1..n])
 *       or
 *          isScramble(s1[0..j], s2[n - j - 1, n]) &&  isScramble(s1[j+1..n], s2[0..n - j])
 */
#define N 128

static bool scramble(char *s1, int low1, int high1, char *s2, int low2, int high2)
{
    if (high1 - low1 != high2 - low2) {
        return false;
    } else if (!memcmp(s1 + low1, s2 + low2, high1 - low1 + 1)) {
        return true;
    } else {
        int i, c1[N], c2[N];
        memset(c1, 0, N * sizeof(int));
        memset(c2, 0, N * sizeof(int));
        for (i = low1; i <= high1; i++) {
            c1[s1[i]]++;
        }
        for (i = low2; i <= high2; i++) {
            c2[s2[i]]++;
        }
        if (memcmp(c1, c2, N * sizeof(int))) {
            return false;
        } else {
            int len = high1 - low1 + 1;
            for (i = 1; i < len; i++) {
                if (scramble(s1, low1, low1 + i - 1, s2, low2, low2 + i - 1) &&
                    scramble(s1, low1 + i, high1, s2, low2 + i, high2)) {
                    return true;
                }
                if (scramble(s1, low1, low1 + i - 1, s2, high2 - i + 1, high2) &&
                    scramble(s1, low1 + i, high1, s2, low2, high2 - i)) {
                    return true;
                }
            }
            return false;
        }
    }
}

static bool isScramble(char* s1, char* s2)
{
    return scramble(s1, 0, strlen(s1) - 1, s2, 0, strlen(s2) - 1);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test s1 s2\n");
        exit(-1);
    }
    printf("%s\n", isScramble(argv[1], argv[2]) ? "true" : "false");
    return 0;
}
