#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int maximalRectangle(char** matrix, int matrixRowSize, int matrixColSize) {
    int i, j, max_area = 0;
    for (i = 0; i < matrixRowSize; i++) {
        for (j = 0; j < matrixColSize; j++) {
            if (matrix[i][j] == '1') {
                int area = 0, x, y;
                int row = i;
                int min_col = matrixColSize;
                while (row < matrixRowSize) {
                    for (x = j; x < matrixColSize && matrix[row][x] == '1'; x++) {}
                    min_col = x < min_col ? x : min_col;
                    area = (row - i + 1) * (min_col - j);
                    max_area = area > max_area ? area : max_area;
                    row++;
                }
                int col = j;
                int min_row = matrixRowSize;
                while (col < matrixColSize) {
                    for (y = i; y < matrixRowSize && matrix[y][col] == '1'; y++) {}
                    min_row = y < min_row ? y : min_row;
                    area = (min_row - i) * (col - j + 1);
                    max_area = area > max_area ? area : max_area;
                    col++;
                }
            }
        }
    }
    return max_area;
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
    printf("%d\n", maximalRectangle(argv + 1, argc - 1, strlen(argv[1])));
    return 0;
}
