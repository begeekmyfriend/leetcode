#include <stdio.h>
#include <stdlib.h>

static int removeDuplicates(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return 0;
    }

    int i;
    int len = 0;
    int count = 1;
    for (i = 1; i < numsSize; i++) {
        /* Find the start position to be replaced */
        if (nums[len] == nums[i]) {
            if (count < 2) {
                count++;
                /* Replace in each iteration */
                nums[++len] = nums[i];
            }
        } else {
            /* Here there are more than 2 duplicates */
            count = 1;
            nums[++len] = nums[i];
        }
    }

    return len + 1;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    count = removeDuplicates(nums, count);
    for (i = 0; i < count; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
