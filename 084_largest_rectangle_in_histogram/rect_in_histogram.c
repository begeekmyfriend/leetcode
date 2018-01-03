#include <stdio.h>
#include <stdlib.h>

static int largestRectangleArea(int* heights, int heightsSize)
{
    int *indexes = malloc(heightsSize * sizeof(int));
    int *left = malloc(heightsSize * sizeof(int));
    int *right = malloc(heightsSize * sizeof(int));

    int i, pos = 0;
    for (i = 0; i < heightsSize; i++) {
        /* monotonous increasing stack */
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        left[i] = pos == 0 ? -1 : indexes[pos - 1];
        indexes[pos++] = i;
    }

    pos = 0;
    for (i = heightsSize - 1; i >= 0; i--) {
        /* monotonous increasing stack */
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        right[i] = pos == 0 ? heightsSize : indexes[pos - 1];
        indexes[pos++] = i;
    }

    int max_area = 0;
    for (i = 0; i < heightsSize; i++) {
        int area = heights[i] * (right[i] - left[i] - 1);
        max_area = area > max_area ? area : max_area;
    }

    return max_area;
}

int main(void)
{
    int nums[] = { 2, 1, 5, 6, 2, 3 };
    int count = sizeof(nums) / sizeof(*nums);
    printf("%d\n", largestRectangleArea(nums, count));
    return 0;
}
