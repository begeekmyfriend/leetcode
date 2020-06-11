#include <stdio.h>
#include <stdlib.h>

static int trailingZeroes(int n)
{
    /* As 10 = 2 * 5 so we just count how many fives in it */
    return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%d\n", trailingZeroes(atoi(argv[1])));
    return 0;
}
