#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*
 * RED = 0
 * WHITE = 1
 * BLUE = 2
 */
static void sortColors(int* nums, int numsSize)
{
    int i = 0, j = numsSize - 1;
    while (i < j) {
        while (nums[i] == 0 && i < j) {
            i++;
        }
        while (nums[j] != 0 && j > i) {
            j--;
        }
        swap(nums + i, nums + j);
    }
    j = numsSize - 1;
    while (i < j) {
        while (nums[i] == 1 && i < j) {
            i++;
        }
        while (nums[j] != 1 && j > i) {
            j--;
        }
        swap(nums + i, nums + j);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test colors\n");
        exit(-1);
    }
    int i, count = strlen(argv[1]);
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = argv[1][i] - '0';
    }
    sortColors(nums, count);
    for (i = 0; i < count; i++) {
        printf("%d", nums[i]);
    }
    printf("\n");
    return 0;
}
