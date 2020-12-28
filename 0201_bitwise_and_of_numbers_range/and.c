#include <stdio.h>
#include <stdlib.h>

static int rangeBitwiseAnd(int m, int n)
{
    int i, res = 0;
    for (i = 0; m > 0 && n > 0; i++) {
        if (m == n && (m & 1)) {
            res |= 1 << i;
        }

        m = m >> 1;
        n = n >> 1;
    }

    return res;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test m n\n");
        exit(-1);
    }

    printf("%d\n", rangeBitwiseAnd(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
