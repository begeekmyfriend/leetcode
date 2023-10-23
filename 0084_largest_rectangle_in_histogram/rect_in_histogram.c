#include <stdio.h>
#include <stdlib.h>

static int largestRectangleArea(int* heights, int heightsSize)
{
    int *idx_stk = malloc(heightsSize * sizeof(int));
    int *lmax = malloc(heightsSize * sizeof(int));
    int *rmax = malloc(heightsSize * sizeof(int));

    int i, pos = 0;
    for (i = 0; i < heightsSize; i++) {
        /* keep monotonous increasing stack */
        while (pos > 0 && heights[i] < heights[idx_stk[pos - 1]]) {
            pos--;
        }
        lmax[i] = pos == 0 ? -1 : idx_stk[pos - 1];
        idx_stk[pos++] = i;
    }

    pos = 0;
    for (i = heightsSize - 1; i >= 0; i--) {
        /* keep monotonous increasing stack */
        while (pos > 0 && heights[i] < heights[idx_stk[pos - 1]]) {
            pos--;
        }
        rmax[i] = pos == 0 ? heightsSize : idx_stk[pos - 1];
        idx_stk[pos++] = i;
    }

    int max_area = 0;
    for (i = 0; i < heightsSize; i++) {
        int area = heights[i] * (rmax[i] - lmax[i] - 1);
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
