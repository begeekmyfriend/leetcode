#include <stdio.h>
#include <stdlib.h>

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int jump(int* nums, int numsSize)
{
    int i, lo = 0, hi = 0;
    int steps = 0;
    while (hi < numsSize - 1) {
        int right = 0;
        for (i = lo; i <= hi; i++) {
            right = max(i + nums[i], right);
        }
        lo = hi + 1;
        hi = right;
        steps++;
    }
    return steps;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", jump(nums, count));
    return 0;
}
