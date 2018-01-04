#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dfs(char** grid, int row_size, int col_size, int row, int col)
{
    grid[row][col] = '0';

    if (row > 0 && grid[row - 1][col] == '1') {
        dfs(grid, row_size, col_size, row - 1, col);
    }

    if (row < row_size - 1 && grid[row + 1][col] == '1') {
        dfs(grid, row_size, col_size, row + 1, col);
    }

    if (col > 0 && grid[row][col - 1] == '1') {
        dfs(grid, row_size, col_size, row, col - 1);
    }

    if (col < col_size - 1 && grid[row][col + 1] == '1') {
        dfs(grid, row_size, col_size, row, col + 1);
    }
}

static int numIslands(char** grid, int gridRowSize, int gridColSize)
{
    int i, j, count = 0;
    for (i = 0; i < gridRowSize; i++) {
        for (j = 0; j < gridColSize; j++) {
            if (grid[i][j] == '1') {
                dfs(grid, gridRowSize, gridColSize, i, j);
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test 11000 11000 00100 00011\n");
        exit(-1);
    }

    int i, j;
    int row_size = argc - 1;
    int col_size = strlen(argv[1]);
    char **grid = malloc(row_size * sizeof(char *));
    for (i = 0; i < row_size; i++) {
            grid[i] = malloc(col_size);
            memcpy(grid[i], argv[i + 1], col_size);
    }

    printf("%d\n", numIslands(grid, row_size, col_size));
    return 0;
}
