#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse(int *a, int size)
{
    int left = 0;
    int right = size - 1;
    while (left < right) {
        int tmp = a[left];
        a[left] = a[right];
        a[right] = tmp;
        left++;
        right--;
    }
}

static void next_permute(int* nums, int numsSize) {
    if (numsSize <= 1) {
        return;
    }

    int *p = nums + numsSize - 1;    
    int *q = nums + numsSize - 1;

    while (p != nums && *(p - 1) >= *p) {
        p--;
    }

    if (p != nums) {
        int n = *(p - 1);
        while (*q <= n) {
            q--;
        }

        int tmp = *q;
        *q = *(p - 1);
        *(p - 1) = tmp;
    }
    reverse(p, numsSize - (p - nums));
}

/**
 ** Return an array of arrays of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int** permute(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        return NULL;
    }

    int i, count = 1, size = numsSize;
    while (size > 0) {
        count *= size--;
    }

    int **permutations = malloc(count * sizeof(int *));
    permutations[0] = malloc(numsSize * sizeof(int));
    memcpy(permutations[0], nums, numsSize * sizeof(int));
    for (i = 1; i < count; i++) {
        permutations[i] = malloc(numsSize * sizeof(int));
        memcpy(permutations[i], permutations[i - 1], numsSize * sizeof(int));
        next_permute(permutations[i], numsSize);
    }

    *returnSize = count;
    return permutations;
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./test ...\n");
        exit(-1);
    }

    int i, j, count;
    int *nums = malloc(sizeof(int));
    for (i = 0; i < argc - 1; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    int **lists = permute(nums, argc - 1, &count);

    for (i = 0; i < count; i++) {
        for (j = 0; j < argc - 1; j++) {
            printf("%d", lists[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
