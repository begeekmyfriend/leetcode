#include <stdio.h>
#include <stdlib.h>

static int removeDuplicates(int* nums, int numsSize)
{
    if (numsSize <= 1) {
        return numsSize;
    }

    int i, count = 1;
    for (i = 1; i < numsSize; i++) {
        if (nums[i - 1] != nums[i]) {
            nums[count++] = nums[i];
        }
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
