#include <stdio.h>
#include <stdlib.h>

static void rotate(int** matrix, int matrixRowSize, int matrixColSize)
{
    int i, j;
    if (matrixRowSize != matrixColSize) {
        return;
    }

    for (i = 0; i < matrixRowSize / 2; i++) {
        int low = i, high = matrixColSize - i - 1;
        for (j = low; j < high; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[matrixColSize - 1 - j][i];
            matrix[matrixColSize - 1 - j][i] = matrix[matrixRowSize - 1 - i][matrixColSize - 1 - j];
            matrix[matrixRowSize - 1 - i][matrixColSize - 1 - j] = matrix[j][matrixRowSize - 1 - i];
            matrix[j][matrixRowSize - 1 - i] = tmp;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test 3 3\n");
    }

    int i, j, count = 0;
    int row_size = atoi(argv[1]);
    int col_size = atoi(argv[2]);
    int **matrix = malloc(row_size * sizeof(int *));
    for (i = 0; i < row_size; i++) {
        matrix[i] = malloc(col_size * sizeof(int));
        for (j = 0; j < col_size; j++) {
            matrix[i][j] = ++count;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    rotate(matrix, row_size, col_size);
    for (i = 0; i < col_size; i++) {
        for (j = 0; j < row_size; j++) {
            printf("%02d ", matrix[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
