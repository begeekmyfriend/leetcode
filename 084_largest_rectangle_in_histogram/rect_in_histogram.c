#include <stdio.h>
#include <stdlib.h>

static int largestRectangleArea(int* heights, int heightsSize)
{
    int i, max_area = 0;
    for (i = 0; i < heightsSize; i++) {
        if (i > 0 && heights[i - 1] == heights[i]) {
            continue;
        }
        int low = i;
        int high = i;
        while (low - 1 >= 0 && heights[low - 1] >= heights[i]) {
            low--;
        }
        while (high + 1 < heightsSize && heights[high + 1] >= heights[i]) {
            high++;
        }
        int area = (high - low + 1) * heights[i];
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
