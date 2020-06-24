#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sortColors(int* nums, int numsSize)
{
    int i, j = 0;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            swap(nums + j, nums + i);
            j++;
        }
    }

    for (i = j; i < numsSize; i++) { 
        if (nums[i] == 1) {
            swap(nums + j, nums + i);
            j++;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test 2 0 2 1 1 0\n");
        exit(-1);
    }
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    sortColors(nums, count);
    for (i = 0; i < count; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}
