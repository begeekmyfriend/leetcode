#include <stdio.h>
#include <stdlib.h>

static void setZeroes(int** matrix, int matrixRowSize, int matrixColSize)
{
    int row, col, bRow = 0, bCol = 0;
    for (row = 0; row < matrixRowSize; row++) {
        for (col = 0; col < matrixColSize; col++) {
            if (matrix[row][col] == 0) {
                if (row == 0) bCol = 1;
                if (col == 0) bRow = 1;
                matrix[0][col] = matrix[row][0] = 0;
            }
        }
    }

    for (row = 1; row < matrixRowSize; row++) {
        for(col = 1; col < matrixColSize; col++){
            if (matrix[0][col] == 0 || matrix[row][0] == 0) {
                matrix[row][col] = 0;
            }
        }
    }

    if (bRow) {
        for(row = 0; row < matrixRowSize; row++) {
            matrix[row][0] = 0;
        }
    }

    if (bCol) {
        for (col = 0; col <matrixColSize; col++) {
            matrix[0][col] = 0;
        }
    }
}

int main(int argc, char **argv)
{
    return 0;
}
