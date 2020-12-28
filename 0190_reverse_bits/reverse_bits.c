#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static uint32_t reverseBits(uint32_t n)
{
    int i;
    uint32_t res = 0;
    for (i = 0; i < 32; i++) {
        res <<= 1;
        res |= n & 0x1;
        n >>= 1;
    }
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%u\n", reverseBits(atoi(argv[1])));
    return 0;
}
