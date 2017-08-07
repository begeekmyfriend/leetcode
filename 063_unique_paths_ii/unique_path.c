#include <stdio.h>
#include <stdlib.h>

static int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize)
{
    int row, col;
    int reset = 0;
    for (row = 0; row < obstacleGridRowSize; row++) {
        if (reset) {
            obstacleGrid[row][0] = 1;
        } else {
            if (obstacleGrid[row][0] == 1) {
                reset = 1;
            }
        }
    }

    reset = 0;
    for (col = 0; col < obstacleGridColSize; col++) {
        if (reset) {
            obstacleGrid[0][col] = 1;
        } else {
            if (obstacleGrid[0][col] == 1) {
                reset = 1;
            }
        }
    }

    for (row = 0; row < obstacleGridRowSize; row++) {
        int *line = obstacleGrid[row];
        for (col = 0; col < obstacleGridColSize; col++) {
            line[col] ^= 1;
        }
    }

    for (row = 1; row < obstacleGridRowSize; row++) {
        int *last_line = obstacleGrid[row - 1];
        int *line = obstacleGrid[row];
        for (col = 1; col < obstacleGridColSize; col++) {
            if (line[col] != 0) {
                line[col] = line[col - 1] + last_line[col];
            }
        }
    }

    return obstacleGrid[obstacleGridRowSize - 1][obstacleGridColSize - 1];
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test m n\n");
        exit(-1);
    }

    int i, j, k = 3;
    int row_size = atoi(argv[1]);
    int col_size = atoi(argv[2]);
    int **grids = malloc(row_size * sizeof(int *));
    for (i = 0; i < row_size; i++) {
        grids[i] = malloc(col_size * sizeof(int));
        int *line = grids[i];
        for (j = 0; j < col_size; j++) {
            line[j] = atoi(argv[k++]);
            printf("%d ", line[j]);
        }
        printf("\n");
    }
    printf("%d\n", uniquePathsWithObstacles(grids, row_size, col_size));
    return 0;
}
