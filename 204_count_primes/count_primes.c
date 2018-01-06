#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int countPrimes(int n)
{
    if (n < 3) return 0;
    
    int i, j;
    bool *marked = malloc(n);
    memset(marked, false, n);
    int count = n >> 1;

    for (i = 3; i * i <= n; i += 2) {
        if (!marked[i]) {
            for (j = i * i; j < n; j += (i << 1)) {
                if (!marked[j]) {
                    marked[j] = true;
                    --count;
                }
            }
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%d\n", countPrimes(atoi(argv[1])));
    return 0;
}
