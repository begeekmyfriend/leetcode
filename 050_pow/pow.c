#include <stdio.h>
#include <stdlib.h>

static double fast_pow(double x, int n)
{
    if (n == 0) { return 1.0; }
    if (n == 1) { return x; }
    double t = fast_pow(x, n / 2);
    return n & 1 ? t * t * x : t * t;
}

static double my_pow(double x, int n)
{
    return n < 0 ? 1 / fast_pow(x, -n) : fast_pow(x, n);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test x n\n");
        exit(-1);
    }
    printf("%lf\n", my_pow(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
