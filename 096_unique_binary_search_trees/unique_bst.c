#include <stdio.h>
#include <stdlib.h>

/*
 * f(n) = f(0)f(n-1) + f(1)f(n-2) + ... + f(n-2)f(1) + f(n-1)f(0)
 */

static int numTrees(int n) {
    int i, j;
    int *sum = malloc((n + 1) * sizeof(int));
    sum[0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = 0; j < i; j++) {
            sum[i] += sum[j] * sum[i - j - 1];
        }
    }
    return sum[n];
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }
    printf("%d\n", numTrees(atoi(argv[1])));
    return 0;
}
