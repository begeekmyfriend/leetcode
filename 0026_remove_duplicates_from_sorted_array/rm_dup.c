#include <stdio.h>
#include <stdlib.h>


static int removeDuplicates(int* nums, int numsSize)
{
    int i, size = 0;
    for (i = 1; i < numsSize; i++) {
        if (nums[size] != nums[i]) {
            nums[++size] = nums[i];
        }
    }

    return size + 1;
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
