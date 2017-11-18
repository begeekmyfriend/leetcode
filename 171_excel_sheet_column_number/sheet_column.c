#include <stdio.h>
#include <stdlib.h>

static int titleToNumber(char *s)
{
    int n = 0;
    while (*s != '\0') {
        n *= 26;
        n += *s++ - 'A' + 1;
    }

    return n;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test ABC\n");
        exit(-1);
    }

    printf("%d\n", titleToNumber(argv[1]));
    return 0;
}
