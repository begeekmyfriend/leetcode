#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int reverse(int x)
{
    int y = 0;
    while (x) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
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
