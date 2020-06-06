#include <stdio.h>
#include <stdlib.h>


static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static int trap(int* height, int heightSize)
{
    if (heightSize < 1) {
        return 0;
    }

    int i;
    int *lh = malloc(heightSize * sizeof(int));
    int *rh = malloc(heightSize * sizeof(int));

    /* restore the max height in the left side of [i] (included) */
    lh[0] = height[0];
    for (i = 1; i < heightSize; i++) {
        lh[i] = max(height[i], lh[i - 1]);
    }

    /* restore the max height in the right side of [i] (included) */
    rh[heightSize - 1] = height[heightSize - 1];
    for (i = heightSize - 2; i >= 0; i--) {
        rh[i] = max(height[i], rh[i + 1]);
    }

    int capacity = 0;
    for (i = 0; i < heightSize; i++) {
        capacity += min(lh[i], rh[i]) - height[i];
    }

    return capacity;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", trap(nums, count));
    return 0;
}
