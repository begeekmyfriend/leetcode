#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


static bool isMatch(char *s, char *p)
{
    if (*p == '\0') {
        return *s == '\0';
    }

    bool first_match = (*s != '\0') && (*s == *p || *p == '.'); 

    if (p[1] == '*') {
        return isMatch(s, p + 2) || (first_match && isMatch(s + 1, p));
    } else {
        return first_match && isMatch(s + 1, p + 1);
    }
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
