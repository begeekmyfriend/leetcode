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
static int** permute_unique(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        return NULL;
    }

    int cap = 1, count = 0, stop = 0;
    int **permutations = malloc(cap * sizeof(int *));
    permutations[count] = malloc(numsSize * sizeof(int));
    memcpy(permutations[count], nums, numsSize * sizeof(int));
    count++;

    while (!stop) {
        int *permutation = malloc(numsSize * sizeof(int));
        memcpy(permutation, permutations[count - 1], numsSize * sizeof(int));
        next_permute(permutation, numsSize);
        if (memcmp(permutation, nums, numsSize * sizeof(int))) {
            if (count + 1 >= cap) {
                cap *= 2;
                permutations = realloc(permutations, cap * sizeof(int *));
            }
            permutations[count++] = permutation;
        } else {
            stop = 1;
        }
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

    int **lists = permute_unique(nums, argc - 1, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < argc - 1; j++) {
            printf("%d", lists[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
