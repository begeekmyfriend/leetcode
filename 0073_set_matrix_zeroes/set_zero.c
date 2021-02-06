#include <stdio.h>
#include <stdlib.h>


void setZeroes(int** matrix, int matrixSize, int* matrixColSize)
{
    int row, col;
    bool bRow = false, bCol = false;
    for (row = 0; row < matrixSize; row++) {
        for (col = 0; col < matrixColSize[row]; col++) {
            if (matrix[row][col] == 0) {
                if (row == 0) bRow = true;
                if (col == 0) bCol = true;
                matrix[0][col] = matrix[row][0] = 0;
            }
        }
    }

    for (row = 1; row < matrixSize; row++) {
        for(col = 1; col < matrixColSize[row]; col++){
            if (matrix[0][col] == 0 || matrix[row][0] == 0) {
                matrix[row][col] = 0;
            }
        }
    }

    if (bRow) {
        memset(matrix[0], 0, matrixColSize[0] * sizeof(int));
    }

    if (bCol) {
        for (row = 0; row < matrixSize; row++) {
            matrix[row][0] = 0;
        }
    }
}

int main(int argc, char **argv)
{
    return 0;
}
