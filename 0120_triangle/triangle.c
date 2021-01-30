#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static int dfs(int** triangle, int row_size, int *col_sizes,
               int row, int col, int **sums, bool **passed)
{
    if (row == row_size - 1) {
        return triangle[row][col];
    } else if (passed[row][col]) {
        return sums[row][col];
    } else {
        int s1 = dfs(triangle, row_size, col_sizes, row + 1, col, sums, passed);
        int s2 = dfs(triangle, row_size, col_sizes, row + 1, col + 1, sums, passed);
        sums[row][col] = triangle[row][col] + (s1 < s2 ? s1 : s2);
        /* Set pass marks in backtracing as the paths are overlapped */
        passed[row][col] = true;
        return sums[row][col];
    }
}

int minimumTotal(int** triangle, int triangleSize, int *triangleColSizes)
{
    int i;
    int **sums = malloc(triangleSize * sizeof(int *));
    bool **passed = malloc(triangleSize * sizeof(bool *));
    for (i = 0; i < triangleSize; i++) {
        passed[i] = malloc(triangleColSizes[i]);
        memset(passed[i], false, triangleColSizes[i]);
        sums[i] = malloc(triangleColSizes[i] * sizeof(int));
    }
    return dfs(triangle, triangleSize, triangleColSizes, 0, 0, sums, passed);
}

int main(void)
{
    int i, row = 4;
    int **nums = malloc(row * sizeof(int *));
    int *sizes = malloc(row * sizeof(int));
    for (i = 0; i < row; i++) {
        sizes[i] = i + 1;
        nums[i] = malloc(sizes[i] * sizeof(int));
    }
#if 0
    nums[0][0] = -1;
    nums[1][0] = 3;
    nums[1][1] = 2;
    nums[2][0] = -3;
    nums[2][1] = 1;
    nums[2][2] = -1;
#else
    nums[0][0] = 2;
    nums[1][0] = 3;
    nums[1][1] = 4;
    nums[2][0] = 6;
    nums[2][1] = 5;
    nums[2][2] = 7;
    nums[3][0] = 4;
    nums[3][1] = 1;
    nums[3][2] = 8;
    nums[3][3] = 3;
#endif
    printf("%d\n", minimumTotal(nums, row, sizes));
    return 0;
}
