#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int numsSize) {
    int i = 0, j, x, y, count = 0;
    while (i < numsSize) {
        for (j = i + 1; j < numsSize && nums[i] == nums[j]; j++) {}
        int diff = j - i;
        if (diff > 2) {
            for (x = i + 2, y = j; y < numsSize; x++, y++) {
                nums[x] = nums[y];
            }
            numsSize -= diff - 2;
        }
        count += diff > 2 ? 2 : diff;
        i += diff > 2 ? 2 : diff;
    }
    return count;
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
