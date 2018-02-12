#include <stdio.h>
#include <stdlib.h>

static int trap(int* height, int heightSize)
{
    if (heightSize < 2) {
        return 0;
    }

    int i, j, top0 = -1, top1 = -1, sum = 0, level = 0;
    for (i = 0; i < heightSize; i++) {
        if (height[i] > 0) {
            top0 = i;
            break;
        }
    }

    while (i < heightSize) {
        top1 = -1;
        for (j = i + 1; j < heightSize; j++) {
            if (height[j] >= height[j - 1]) {
                if (top1 < 0 || height[j] >= height[top1]) {
                    top1 = j;
                }
                if (height[j] >= height[top0]) {
                    break;
                }
            }
        }

        if (top1 >= 0) {
            int level = height[top0] < height[top1] ? height[top0] : height[top1];
            while (i < top1) {
                if (level > height[i]) {
                    sum += level - height[i];
                }
                i++;
            }
            top0 = top1;
            i = top1;
        } else {
            i = j;
        }
    }

    return sum;
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
