#include <stdio.h>
#include <stdlib.h>

static int jump(int* nums, int numsSize) {
    if (numsSize <= 1) {
        return 0;
    }

    int i;
    int next_pos = numsSize - 1;
    int pos = next_pos;
    int *indexes = malloc(numsSize * sizeof(int));
    int *p = indexes;

    *p++ = numsSize - 1;
    while (--pos >= 0) {
        for (i = 0; i < p - indexes; i++) {
            if (nums[pos] >= indexes[i] - pos) {
                indexes[i + 1] = pos;
                p = indexes + i + 2;
                break;
            }
        }
    }

    return p - indexes - 1;
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
