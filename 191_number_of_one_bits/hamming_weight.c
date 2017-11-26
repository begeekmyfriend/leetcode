#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int hammingWeight(uint32_t n)
{
    int count = 0;
    while (n > 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%d\n", hammingWeight(atoi(argv[1])));
    return 0;
}
