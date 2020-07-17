#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


static int reverse(int x)
{
    int n = 0;
    while (x != 0) {
        int r = x % 10;
        /* Checking the over/underflow. */
        if (n > INT_MAX / 10 || (n == INT_MAX / 10 && r > 7)) {
            return 0;
        }
        if (n < INT_MIN / 10 || (n == INT_MIN / 10 && r < -8)) {
            return 0;
        }
        n = n * 10 + r;
        x /= 10;
    }
    return n;
}

static bool isPalindrome(int x)
{
    if (x == 0) {
        return true;
    }
    if (x < 0) {
        return false;
    }
    return x == reverse(x);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test number\n");
        exit(-1);
    }

    printf("%s\n", isPalindrome(atoi(argv[1])) ? "true" : "false");
    return 0;
}
