#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static bool isMatch(char* s, char* p)
{
    char *last_s = NULL;
    char *last_p = NULL;
    while (*s != '\0') {
        if (*p == '*') {
            /* skip the '*', and mark a flag */
            if (*++p == '\0') {
                return true;
            }
            /* use last_s and last_p to store where the "*" match starts. */
            last_s = s;
            last_p = p;
        } else if (*p == '?' || *s == *p) {
            s++;
            p++;
        } else if (last_s != NULL) {
            /* check "last_s" to know whether meet "*" before
             * if meet "*" previously, and the *s != *p
             * reset the p, using '*' to match this situation
             */
            p = last_p;
            s = ++last_s;
        } else {
            /* *p is not wildcard char, 
             * doesn't match *s, 
             * there are no '*' wildcard matched before
             */
            return false;
        }
    }

    /* s is done, but "p" still have chars. */
    while (*p == '*') {
        p++;
    }
    return *p == '\0';
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test string pattern\n");
        exit(-1);
    }

    printf("%s\n", isMatch(argv[1], argv[2]) ? "true" : "false");
    return 0;
}
