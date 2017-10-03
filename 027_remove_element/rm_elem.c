#include <stdio.h>
#include <stdlib.h>

static int removeElement(int *nums, int numsSize, int val)
{
    int i, count = 0;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] != val) {
            nums[count++] = nums[i];
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    int i;
    int *nums = malloc((argc - 2) * sizeof(int));
    for (i = 0; i < argc - 2; i++) {
        nums[i] = atoi(argv[i + 2]);
    }

    int count = removeElement(nums, argc - 2, atoi(argv[1]));
    for (i = 0; i < count; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
