#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static uint32_t reverseBits(uint32_t n)
{
    const uint32_t MASK1 = 0x55555555;
    const uint32_t MASK2 = 0x33333333;
    const uint32_t MASK4 = 0x0f0f0f0f;
    const uint32_t MASK8 = 0x00ff00ff;

    // Extract and swap the even and odd bit groups.
    n = (n & MASK1) << 1 | ((n >> 1) & MASK1);
    n = (n & MASK2) << 2 | ((n >> 2) & MASK2);
    n = (n & MASK4) << 4 | ((n >> 4) & MASK4);
    n = (n & MASK8) << 8 | ((n >> 8) & MASK8);
    return n << 16 | n >> 16;
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
