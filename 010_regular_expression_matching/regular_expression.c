#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool isMatch(char* s, char* p)
{
    if (*p == '\0') {
        return *s == '\0';
    }
    /* p's length 1 is special case */
    if (*(p + 1) == '\0' || *(p + 1) != '*') {
        if (*s == '\0' || ( *p != '.' && *s != *p)) {
            return false;
        } else {
            return isMatch(s + 1, p + 1);
        }
    }
    int len = strlen(s);
    int i = -1;
    while (i < len && (i < 0 || *p == '.' || *p == *(s + i))) {
        if (isMatch(s + i + 1, p + 2)) {
            return true;
        }
        i++;
    }
    return false;
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
