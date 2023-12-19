#include <stdio.h>
#include <stdlib.h>


static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static int jump(int* nums, int numsSize)
{
    int i, right = 0;
    int steps = 0;
    int fartest = 0;
    /* 1. Exhaust all the right boundries in the location range of [i...right]
     * 2. When the search ends up with i==right, update the right boundry as
     *    the fartest position.
     * 3. When the search ends up with i==right, it records as one jump step */
    for (i = 0; i < numsSize; i++) {
        fartest = max(i + nums[i], fartest);
        if (i == right) {
            right = fartest;
            steps++;
        }
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
