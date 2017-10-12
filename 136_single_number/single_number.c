#include <stdio.h>
#include <stdlib.h>

static int singleNumber(int *nums, int numsSize)
{
    int i, s = 0;
    for (i = 0; i < numsSize; i++) {
        s ^= nums[i];
    }
    return s;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", singleNumber(nums, count));
    return 0;
}
