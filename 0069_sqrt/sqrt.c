#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#if 0
static double mySqrt(double x)
{
    double lo = 0;
    double hi = x;
    double diff = 1e-8;
    double mid = (lo + hi) / 2;
    while (fabs(mid * mid - x) > diff) {
        if (mid < x / mid) {
            lo = mid;
        } else if (mid > x / mid) {
            hi = mid;
        } else {
            break;
        }
        mid = (lo + hi) / 2;
    }

    return mid;
}

static double mySqrt(double n)
{
    /* Solute the zero point of f(x). Let F(x) = f(x) - n = 0 */
    /* then (x - x0)F'(x0) + F(x0) = 0 which is the first order of Tylor series */
    double x = 1.0;
    while (fabs(x * x - n) > 1e-8) {
        // x = x - (x * x - n) / (2 * x);
        x = (x - n / x) / 2;
    }
    return x;
}

static double mySqrt(double n)
{
    /* Gradient descent
     * MSE Loss = (x * x - n) ^ 2
     * G = 4 * x ^ 3 - 4 * n * x
     * x = x - a * G
     */
    double a = 1e-4;
    double x = 1.0;
    while (fabs(x * x - n) > 1e-8) {
        x = x - a * 4 * x * (x * x - n);
    }
    return x;
}
#endif

static int mySqrt(int x)
{
    if (x == 0) {
        return 0;
    }

    unsigned int left = 1;
    unsigned int right = (unsigned int) x;
    unsigned int mid = left + (right - left) / 2;
    for (; ;) {
        if (mid > x/mid) {
            right = mid;
        } else {
            if (mid + 1 > x/(mid + 1)) {
                break;
            } else {
                left = mid;
            }
        }
        mid = left + (right - left) / 2;
    }

    return mid;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    //printf("%f\n", mySqrt(1.5));//atoi(argv[1])));
    printf("%d\n", mySqrt(atoi(argv[1])));
    return 0;
}
