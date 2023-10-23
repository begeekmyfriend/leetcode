#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int area_calc(int *heights, int size)
{
    int *idx_stk = malloc(size * sizeof(int));
    int *lmax = malloc(size * sizeof(int));
    int *rmax = malloc(size * sizeof(int));

    int i, pos = 0;
    for (i = 0; i < size; i++) {
        /* keep monotonous increasing maxograms */
        while (pos > 0 && heights[i] < heights[idx_stk[pos - 1]]) {
            pos--;
        }
        lmax[i] = pos == 0 ? -1 : idx_stk[pos - 1];
        idx_stk[pos++] = i;
    }

    pos = 0;
    for (i = size - 1; i >= 0; i--) {
        /* keep monotonous increasing maxograms */
        while (pos > 0 && heights[i] < heights[idx_stk[pos - 1]]) {
            pos--;
        }
        rmax[i] = pos == 0 ? size : idx_stk[pos - 1];
        idx_stk[pos++] = i;
    }

    int max_area = 0;
    for (i = 0; i < size; i++) {
        int area = heights[i] * (rmax[i] - lmax[i] - 1);
        max_area = max(area, max_area);
    }

    return max_area;
}

static int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
    int i, j, max_area = 0;
    int *heights = malloc(matrixColSize[0] * sizeof(int));
    memset(heights, 0, matrixColSize[0] * sizeof(int));
    for (i = 0; i < matrixSize; i++) {
        for (j = 0; j < matrixColSize[i]; j++) {
            heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
        }
        max_area = max(max_area, area_calc(heights, matrixColSize[i]));
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
    int *cols = malloc(row_size * sizeof(int));
    for (i = 0; i < row_size; i++) {
        cols[i] = strlen(argv[1]);
        printf("%s\n", argv[i + 1]);
    }
    printf("%d\n", maximalRectangle(argv + 1, argc - 1, cols));
    return 0;
}
