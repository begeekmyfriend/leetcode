#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static bool canJump(int* nums, int numsSize)
{
    int i, pos = 0;
    for (i = 0; i < numsSize - 1; i++) {
        if (pos < i || pos >= numsSize - 1) {
            break;
        }
        pos = max(i + nums[i], pos);
    }

    return pos >= numsSize - 1;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%s\n", canJump(nums, count) ? "true" : "false");
    return 0;
}
