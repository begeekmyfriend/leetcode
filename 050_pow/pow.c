#include <stdio.h>
#include <stdlib.h>

static double my_pow(double x, int n)
{
    int sign = 0;
    if (n < 0) {
        n = -n;
        sign = 1;
    }

    double res = 1;
    while (n > 0) {
        if (n & 0x1) {
            res *= x;
        }
        x *= x;
        n >>= 1;
    }

    return sign ? 1 / res : res;
}

int main(int argc, char **argv)
{
    printf("%lf\n", my_pow(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
