#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int maximalSquare(char** matrix, int matrixRowSize, int matrixColSize)
{
    int i, j, max_len = 0;
    int **lens = malloc(matrixRowSize * sizeof(int *));
    for (i = 0; i < matrixRowSize; i++) {
        lens[i] = malloc(matrixColSize * sizeof(int));
    }

    for (i = 0; i < matrixColSize; i++) {
        lens[0][i] = matrix[0][i] == '1' ? 1 : 0;
        max_len = matrix[0][i] == '1' ? 1 : max_len;
    }

    for (i = 0; i < matrixRowSize; i++) {
        lens[i][0] = matrix[i][0] == '1' ? 1 : 0;
        max_len = matrix[i][0] == '1' ? 1 : max_len;
    }

    for (i = 1; i < matrixRowSize; i++) {
        for (j = 1; j < matrixColSize; j++) {
            if (matrix[i][j] == '1') {
                lens[i][j] = 1;
                lens[i][j] += min(lens[i - 1][j - 1], min(lens[i - 1][j], lens[i][j - 1]));
            } else {
                lens[i][j] = 0;
            }
            max_len = max(max_len, lens[i][j]);
        }
    }
    return max_len * max_len;
}

/* ./test 11111111 11111110 11111110 11111000 01111000 */
int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test row1 row2...\n");
        exit(-1);
    }

    int i, j;
    int row_size = argc - 1;
    int col_size = strlen(argv[1]);
    for (i = 0; i < row_size; i++) {
        printf("%s\n", argv[i + 1]);
    }
    printf("%d\n", maximalSquare(argv + 1, argc - 1, strlen(argv[1])));
    return 0;
}
