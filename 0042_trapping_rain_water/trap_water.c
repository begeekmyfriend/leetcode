#include <stdio.h>
#include <stdlib.h>

#if 0
static int trap(int* height, int heightSize)
{
    int i, res = 0;
    int *lmax = malloc(heightSize * sizeof(int));
    int *rmax = malloc(heightSize * sizeof(int));

    lmax[0] = height[0];
    rmax[heightSize - 1] = height[heightSize - 1];

    for (i = 1; i < heightSize; i++) {
        lmax[i] = height[i] > lmax[i - 1]  ? height[i] : lmax[i - 1] ;
    }

    for (i = heightSize - 2; i >= 0; i--) {
        rmax[i] = height[i] > rmax[i + 1]  ? height[i] : rmax[i + 1] ;
    }

    for (i = 1; i < heightSize - 1; i++) {
        res += (lmax[i]  < rmax[i]  ? lmax[i]  : rmax[i] ) - height[i];
    }

    return res;
}
#endif

static int trap(int* height, int heightSize)
{
    /* In fact if we find the relative higher bar position and then the
     * water level of the position would be determined by the opposite side.
     */
    int res = 0;
    int l = 0, lmax = 0;
    int r = heightSize - 1, rmax = 0;

    while (l < r) {
        /* lmax is the highest in height[0...l] and
         * rmax is the highest in height[r...size - 1]
         */
        lmax = height[l] > lmax ? height[l] : lmax;
        rmax = height[r] > rmax ? height[r] : rmax;
        if (lmax < rmax) {
            res += lmax - height[l];
            l++;
        } else {
            res += rmax - height[r];
            r--;
        }
    }

    return res;
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
