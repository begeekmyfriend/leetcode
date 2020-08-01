#include <stdio.h>
#include <stdlib.h>

static void rotate(int** matrix, int matrixSize, int *matrixColSize)
{
    int i, j;
    for (i = 0; i < matrixSize / 2; i++) {
        int col_size = matrixColSize[i];
        int low = i, high = col_size - i - 1;
        for (j = low; j < high; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[col_size - 1 - j][i];
            matrix[col_size - 1 - j][i] = matrix[matrixSize - 1 - i][col_size - 1 - j];
            matrix[matrixSize - 1 - i][col_size - 1 - j] = matrix[j][matrixSize - 1 - i];
            matrix[j][matrixSize - 1 - i] = tmp;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test 3\n");
    }

    int i, j, count = 0;
    int row_size = atoi(argv[1]);
    int *col_sizes = malloc(row_size * sizeof(int));
    int **matrix = malloc(row_size * sizeof(int *));
    for (i = 0; i < row_size; i++) {
        col_sizes[i] = row_size;
        matrix[i] = malloc(col_sizes[i] * sizeof(int));
        for (j = 0; j < col_sizes[i]; j++) {
            matrix[i][j] = ++count;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    rotate(matrix, row_size, col_sizes);
    for (i = 0; i < row_size; i++) {
        for (j = 0; j < col_sizes[i]; j++) {
            printf("%02d ", matrix[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
