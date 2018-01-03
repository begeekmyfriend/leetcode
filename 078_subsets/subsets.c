#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dfs(int *nums, int size, int start, int *buf,
                int len, int **sets, int *sizes, int *count)
{
    int i;
    sets[*count] = malloc(len * sizeof(int));
    memcpy(sets[*count], buf, len * sizeof(int));
    sizes[*count] = len;
    (*count)++;
    for (i = start; i < size; i++) {
        buf[len] = nums[i];
        dfs(nums, size, i + 1, buf, len + 1, sets, sizes, count);
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
int** subsets(int* nums, int numsSize, int** columnSizes, int* returnSize)
{
    int capacity = 5000;
    int **sets = malloc(capacity * sizeof(int *));
    int *buf = malloc(numsSize * sizeof(int));
    *columnSizes = malloc(capacity * sizeof(int));
    *returnSize = 0;
    dfs(nums, numsSize, 0, buf, 0, sets, *columnSizes, returnSize);
    return sets;
}

int main(int argc, char **argv)
{
    int i, j;
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./test array...\n");
        exit(-1);
    }
    int size = argc - 1;
    int *nums = malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    int *sizes;
    int count;
    int **lists = subsets(nums, size, &sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
