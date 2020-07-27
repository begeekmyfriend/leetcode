#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static inline int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void dfs(int *nums, int size, int start, int *buf,
                int level, int **sets, int *count, int *sizes)
{
    int i, last = INT_MIN;
    sets[*count] = malloc(level * sizeof(int));
    memcpy(sets[*count], buf, level * sizeof(int));
    sizes[*count] = level;
    (*count)++;
    for (i = start; i < size; i++) {
        if (last != nums[i]) {
            /* No duplicate candidate elements at same level position */
            buf[level] = nums[i];
            /* i + 1 limits the selecting range in next levels */
            dfs(nums, size, i + 1, buf, level + 1, sets, count, sizes);
        }
        last = nums[i];
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *returnColumnSizes array.
 ** Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 **/
static int** subsetsWithNoDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), compare);
    int capacity = 5000;
    int **sets = malloc(capacity * sizeof(int *));
    int *buf = malloc(numsSize * sizeof(int));
    *returnColumnSizes = malloc(capacity * sizeof(int));
    *returnSize = 0;
    dfs(nums, numsSize, 0, buf, 0, sets, returnSize, *returnColumnSizes);
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
    int **lists = subsets(nums, size, &count, &sizes);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
