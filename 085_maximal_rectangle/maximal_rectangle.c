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
    int *indexes = malloc(size * sizeof(int));
    int *left = malloc(size * sizeof(int));
    int *right = malloc(size * sizeof(int));

    int i, pos = 0;
    for (i = 0; i < size; i++) {
        /* monotonous increasing stack */
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        left[i] = pos == 0 ? -1 : indexes[pos - 1];
        indexes[pos++] = i;
    }

    pos = 0;
    for (i = size - 1; i >= 0; i--) {
        /* monotonous increasing stack */
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        right[i] = pos == 0 ? size : indexes[pos - 1];
        indexes[pos++] = i;
    }

    int max_area = 0;
    for (i = 0; i < size; i++) {
        int area = heights[i] * (right[i] - left[i] - 1);
        max_area = max(area, max_area);
    }

    return max_area;
}

static int maximalRectangle(char** matrix, int matrixRowSize, int matrixColSize)
{
    int i, j, max_area = 0;
    int *heights = malloc(matrixColSize * sizeof(int));
    memset(heights, 0, matrixColSize * sizeof(int));
    for (i = 0; i < matrixRowSize; i++) {
        for (j = 0; j < matrixColSize; j++) {
            heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
        }
        max_area = max(max_area, area_calc(heights, matrixColSize));
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
