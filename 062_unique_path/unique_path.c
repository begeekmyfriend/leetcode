#include <stdio.h>
#include <stdlib.h>

static int uniquePaths(int m, int n)
{
    int row, col;
    int *grids = malloc(m * n * sizeof(int));
    for (col = 0; col < m; col++) {
        grids[col] = 1;
    }
    for (row = 0; row < n; row++) {
        grids[row * m] = 1;
    }
    for (row = 1; row < n; row++) {
        for (col = 1; col < m; col++) {
            grids[row * m + col] = grids[row * m + col - 1] + grids[(row - 1) * m + col];
        }
    }
    return grids[m * n - 1];
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test m n\n");
        exit(-1);
    }
    printf("%d\n", uniquePaths(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
