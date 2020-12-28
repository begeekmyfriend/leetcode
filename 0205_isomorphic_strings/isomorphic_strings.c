#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isIsomorphic(char *s, char *t)
{
    int i;
    char smap[128] = { '\0' };
    char tmap[128] = { '\0' };
    while (*s != '\0' && *t != '\0') {
        if ((smap[*s] != '\0' && smap[*s] != *t) ||
            (tmap[*t] != '\0' && tmap[*t] != *s)) {
            return false;
        }
        smap[*s] = *t;
        tmap[*t] = *s;
        s++;
        t++;
    }
    return *s == *t;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test s1 s2\n");
        exit(-1);
    }

    printf("%s\n", isIsomorphic(argv[1], argv[2]) ? "true" : "false");
    return 0;
}
