#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int dfs(int n, int *count)
{
    if (n == 0) {
        return 0;
    } else if (count[n] > 0) {
        return count[n];
    } else {
        if (n >= 1) {
            count[n] += dfs(n - 1, count);
        }
        if (n >= 2) {
            count[n] += dfs(n - 2, count);
        }
        return count[n];
    }
}

static int climbStairs(int n)
{
#if 0
    int *count = malloc((n + 1) * sizeof(int));
    memset(count, 0, (n + 1) * sizeof(int));
    count[1] = 1;
    count[2] = 2;
    return dfs(n, count);
#else
    int i, a = 1, b = 2, c;
    for (i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return n == 1 ? a : (n == 2 ? b : c);
#endif
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    printf("%d\n", climbStairs(atoi(argv[1])));
    return 0;
}
