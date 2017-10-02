#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void parse(char *input, char *output)
{
    char *p = input;
    char *q = output;

    while (*p != '\0') {
        int count = 1;
        while (p[0] == p[1]) {
            count++;
            p++;
        }

        /* reverse number */
        int n = 0;
        while (count > 0) {
            n += count % 10;
            count /= 10;
        }

        /* parse count */
        while (n > 0) {
            *q++ = (n % 10) + '0';
            n /= 10;
        }

        *q++ = p[0];
        p++;
    }

    *q = '\0';
}

static char *countAndSay(int n)
{
    if (n < 1) {
        return NULL;
    }

    char *result;
    char *prev = malloc(10000);
    char *next = malloc(10000);
    strcpy(prev, "1");

    if (n == 1) {
        return prev;
    }

    int i;
    for (i = 2; i <= n; i++) {
        if (i & 0x1) {
           parse(next, prev);
           result = prev;
        } else {
           parse(prev, next);
           result = next;
        }
    }

    return result;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%s\n", countAndSay(atoi(argv[1])));
    return 0;
}
