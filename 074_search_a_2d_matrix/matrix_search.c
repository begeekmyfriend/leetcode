#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int binary_search(int *nums, int len, int target)
{
    int low = -1;
    int high = len;
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (high == len || nums[high] != target) {
        return -high - 1;
    } else {
        return high;
    }
}

static bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target)
{
    if (matrixRowSize == 0 || matrixColSize == 0) {
        return false;
    }

    if (target < matrix[0][0] || target > matrix[matrixRowSize - 1][matrixColSize - 1]) {
        return false;
    }

    int row = 0;
    int *nums = NULL;
    if (matrixRowSize > 0) {
        nums = malloc(matrixRowSize * sizeof(int));
        for (row = 0; row < matrixRowSize; row++) {
            nums[row] = matrix[row][0];
        }
        row = binary_search(nums, matrixRowSize, target);
        if (row >= 0) {
            return true;
        } else {
            row = -row - 1;
            if (row == 0) {
                return false;
            } else {
                row--;
            }
        }
    }
    int col = binary_search(matrix[row], matrixColSize, target);
    return col >= 0;
}

int main(int argc, char **argv)
{
    int row = 3;
    int col = 4;
    int **mat = malloc(row * sizeof(int *));
    mat[0] = malloc(col * sizeof(int));
    mat[0][0] = 1;
    mat[0][1] = 3;
    mat[0][2] = 5;
    mat[0][3] = 7;
    mat[1] = malloc(col * sizeof(int));
    mat[1][0] = 10;
    mat[1][1] = 11;
    mat[1][2] = 16;
    mat[1][3] = 20;
    mat[2] = malloc(col * sizeof(int));
    mat[2][0] = 23;
    mat[2][1] = 30;
    mat[2][2] = 34;
    mat[2][3] = 50;
    printf("%s\n", searchMatrix(mat, row, col, atoi(argv[1])) ? "true" : "false");
    return 0;
}
