#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool canJump(int* nums, int numsSize) {
    if (numsSize == 0) return false;

    int i = numsSize - 1, j;
    while (i > 0) {
        if (nums[--i] == 0) {
            for (j = i - 1; j >= 0; j--) {
                if (nums[j] > i - j) {
                    break;
                }
            }
            if (j == -1) {
                return false;
            }
        }
    }

    return true;
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
