#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool recursive(int n, bool *used, const int *sq)
{
    if (n == 1) return true;
    if (n < 10000) {
        if (used[n]) return false;
        used[n] = true;
    }
    int sum = 0;
    while (n > 0) {
        sum += sq[n % 10];
        n /= 10;
    }
    return recursive(sum, used, sq);
}

static bool isHappy(int n)
{
    bool used[10000] = { false };
    const static int sq[10] = { 0, 1, 4, 9, 16, 25, 36, 49, 64, 81 };
    return recursive(n, used, sq);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%s\n", isHappy(atoi(argv[1])) ? "true" : "false");
    return 0;
}
