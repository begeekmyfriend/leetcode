#include <stdio.h>
#include <stdlib.h>

static void bubble_sort(int *nums, int *indexes, int size)
{
    int i, flag = size;
    while (flag > 0) {
        int len = flag;
        flag = 0;
        for (i = 1; i < len; i++) {
            if (nums[i] < nums[i - 1]) {
                int tmp = nums[i];
                nums[i] = nums[i - 1];
                nums[i - 1] = tmp;
                tmp = indexes[i];
                indexes[i] = indexes[i - 1];
                indexes[i - 1] = tmp;
                flag = i;
            }
        }
    }
}

static int * twosum(int *nums, int numsSize, int target)
{
    int i, j;
    int *indexes = malloc(numsSize * sizeof(int));
    for (i = 0; i < numsSize; i++) {
        indexes[i] = i;
    }
    bubble_sort(nums, indexes, numsSize);
    
    int count = 0;
    int *results = malloc(2 * sizeof(int));
    i = 0;
    j = numsSize - 1;
    while (i < j) {
        int diff = target - nums[i];
        if (diff > nums[j]) {
            while (++i < j && nums[i] == nums[i - 1]) {}
        } else if (diff < nums[j]) {
            while (--j > i && nums[j] == nums[j + 1]) {}
        } else {
            results[0] = indexes[i];
            results[1] = indexes[j];
            return results;
        }
    }
    return NULL;
}

int main(void)
{
    //int nums[] = {-1, -2, -3, -4, -5};
    //int target = -8;
    //int nums[] = {0,4,3,0};
    //int target = 0;
    int nums[] = { 3, 2, 3 };
    int count = sizeof(nums) / sizeof(*nums);
    int target = 6;
    int *indexes = twosum(nums, count, target);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }

    return 0;
}
