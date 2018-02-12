#include <stdio.h>
#include <stdlib.h>

static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static int firstMissingPositive(int* nums, int numsSize)
{
    if (numsSize < 1) {
        return 1;
    }

    int i = 0;
    while (i < numsSize) {
        if (nums[i] != i + 1 && nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1]) {
            swap(nums + i, nums + nums[i] - 1);
        } else {
            i++;
        }
    }

    for (i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) break;
    }
    return i + 1;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", firstMissingPositive(nums, count));
    return 0;
}
