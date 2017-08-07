#include <stdio.h>
#include <stdlib.h>

static void valid_path_recursive(int col, int m, int row, int n, int *count)
{
    if (col == m - 1 && row == n - 1) {
        (*count)++;
    } else {
        if (m > n) {
            if (col < m - 1) {
                valid_path(col + 1, m, row, n, count);
            }
            if (row < n - 1) {
                valid_path(col, m, row + 1, n, count);
            }
        } else {
            if (col < m - 1) {
                valid_path(col + 1, m, row, n, count);
            }
            if (row < n - 1) {
                valid_path(col, m, row + 1, n, count);
            }
        }
    }
}

static int uniquePaths(int m, int n) {
    //int count = 0;
    //valid_path(0, m, 0, n, &count);
    //return count;
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
    int result = grids[m * n - 1];
    free(grids);
    return result;
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
