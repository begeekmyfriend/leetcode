#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
 * n == 2(10) -- 2 -- res = 1 * 2^2
 * n == 3(11) -- 2 + 1 -- res = 1 * 2^1 * 2^2
 * n == 4(100) -- 4 -- res = 1 * 2^4
 * n == 5(101) -- 4 + 1 -- res = 1 * 2^1 * 2^4
 * n == 6(110) -- 4 + 2 + 1 -- res = 1 * 2^1 * 2^2 * 2^4
 */
static double my_pow(double x, int n)
{
    int orig = x;
    int sign = 0;
    int one_more = 0;
    if (n < 0) {
        if (n == INT_MIN) {
            n = INT_MAX;
            one_more = 1;
        } else {
            n = -n;
        }
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
    if (one_more) {
        res *= orig;
    }

    return sign ? 1 / res : res;
}

int main(int argc, char **argv)
{
    printf("%lf\n", my_pow(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
