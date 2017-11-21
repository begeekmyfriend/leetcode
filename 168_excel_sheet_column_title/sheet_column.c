#include <stdio.h>
#include <stdlib.h>

static char *convertToTitle(int n)
{
    if (n <= 0) {
        return "";
    }

    char *result = malloc(1024);
    int len = 0;
    do {
        result[len++] = ((n - 1) % 26) + 'A';
        n = (n - 1) / 26;
    } while (n > 0);
    result[len] = '\0';

    int i, j;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        char c = result[i];
        result[i] = result[j];
        result[j] = c;
    }
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%s\n", convertToTitle(atoi(argv[1])));
    return 0;
}
