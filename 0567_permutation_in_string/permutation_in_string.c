#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool checkInclusion(char * s1, char * s2)
{
    int i, count[128] = { -1 }, pat_len = 0;
    for (i = 0; s1[i] != '\0'; i++) {
        count[s1[i]]++;
        pat_len++;
    }

    int l = 0, r = 0, len = 0;
    while (s2[r] != '\0') {
        if (--count[s2[r++]] >= 0) {
            len++;
        }
        while (r - l >= pat_len) {
            if (len == pat_len) {
                return true;
            }
            if (++count[s2[l++]] > 0) {
                len--;
            }
        }
    }

    return false;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test string pattern\n");
        exit(-1);
    }

    char *t = argv[1];
    char *s = argv[2];
    printf("%s\n", checkInclusion(t, s) ? "true" : "false");
    return 0;
}
