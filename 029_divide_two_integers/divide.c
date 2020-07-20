#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int divide(int dividend, int divisor)
{
    int signal = 1;
    unsigned int dvd = dividend;
    if (dividend < 0) {
        signal *= -1;
        dvd = ~dvd + 1;
    }

    unsigned int dvs = divisor;
    if (divisor < 0) {
        signal *= -1;
        dvs = ~dvs + 1;
    }

    int shift = 0;
    while (dvd > dvs << shift) {
        shift++;
    }

    unsigned int res = 0;
    while (dvd >= dvs) {
        while (dvd < dvs << shift) {
            shift--;
        }
        res |= (unsigned int) 1 << shift;
        dvd -= dvs << shift;
    }

    if (signal == 1 && res >= INT_MAX) {
        return INT_MAX;
    } else {
        return res * signal;
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test dividend divisor\n");
        exit(-1);
    }
    printf("%d\n", divide(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
