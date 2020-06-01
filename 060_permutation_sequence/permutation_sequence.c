#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* getPermutation(int n, int k)
{
    int i;
    char *result = malloc(n + 1);
    bool *used = malloc(n * sizeof(bool));
    memset(used, false, n * sizeof(bool));

    int total = 1;
    for (i = 1; i <= n; i++) {
        total *= i; /* n! */
    }    

    k = k - 1; /* Begin with 0 */
    for (i = 0; i < n; i++) {
        /* Total elements in each group */
        total /= (n - i);
        int gid = k / total;
        k %= total;

        int x = -1;
        int count = 0;
        /* Search in the remaining numbers */
        while (count <= gid) {
            x = (x + 1) % n;
            if (!used[x]) {
                count++;
            }
        }
        used[x] = true;
        result[i] = x + 1 + '0';
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
