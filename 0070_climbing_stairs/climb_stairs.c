#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int dfs(int n, int *count)
{
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    } else if (count[n] > 0) {
        return count[n];
    } else {
        count[n] += dfs(n - 1, count);
        count[n] += dfs(n - 2, count);
        return count[n];
    }
}

static int climbStairs(int n)
{
#if 1
    if (n < 1) return 0;
    int *count = malloc((n + 1) * sizeof(int));
    memset(count, 0, (n + 1) * sizeof(int));
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
