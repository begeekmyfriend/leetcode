#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int factorial(int n)
{
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

static char* getPermutation(int n, int k)
{
    int i;
    int *permutation = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        permutation[i] = i + 1;
    }

    char *result = malloc(n + 1);
    for (i = 0; i < n; i++) {
        int fac = factorial(n - i - 1);
        int j = k > 1 ? (k - 1) / fac : 0;
        result[i] = permutation[j] + '0';
        k -= j * fac;
        memmove(permutation + j, permutation + j + 1, (n - j) * sizeof(int));
    }
    result[n] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test n, k\n");
        exit(-1);
    }

    printf("%s\n", getPermutation(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
