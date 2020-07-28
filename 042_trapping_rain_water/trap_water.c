#include <stdio.h>
#include <stdlib.h>


static int trap(int* height, int heightSize)
{
    /* In fact if we find the relative higher bar position and then the
     * water level of the position would be determined by the opposite side.
     */
    int res = 0;
    int l = 0, lmax = 0;
    int r = heightSize - 1, rmax = 0;
    while (l < r) {
        if (height[l] < height[r]) {
            if (height[l] > lmax) {
                lmax = height[l];
            } else {
                res += lmax - height[l];
            }
            l++;
        } else {
            if (height[r] > rmax) {
                rmax = height[r];
            } else {
                res += rmax - height[r];
            }
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
