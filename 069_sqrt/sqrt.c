#include <stdio.h>
#include <stdlib.h>

static int mySqrt(int x)
{
    if (x == 0) {
        return 0;
    }

    unsigned int left = 1;
    unsigned int right = (unsigned int) x;
    for (; ;) {
        unsigned int mid = left + (right - left) / 2;
        if (mid > x/mid) {
            right = mid;
        } else {
            if (mid + 1 > x/(mid + 1)) {
                return mid;
            } else {
                left = mid;
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%d\n", mySqrt(atoi(argv[1])));
    return 0;
}
