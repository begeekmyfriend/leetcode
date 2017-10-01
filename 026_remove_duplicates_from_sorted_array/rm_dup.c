#include <stdio.h>
#include <stdlib.h>

static int removeDuplicates(int* nums, int numsSize)
{
    if (numsSize <= 1) {
        return numsSize;
    }

    int i = 0, j, count = 1;
    while (i < numsSize) {
        for (j = i + 1; j < numsSize && nums[i] == nums[j]; j++) {}
        if (j < numsSize) {
            nums[count++] = nums[j];
        }
        i = j;
    }

    return count;
}

int main(int argc, char **argv)
{
    int i, size = argc - 1;
    int *nums = malloc(size * sizeof(int));
    for (i = 0; i < argc - 1; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    int count = removeDuplicates(nums, size);
    for (i = 0; i < count; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}
