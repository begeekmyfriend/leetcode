#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static inline int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void dfs(int *nums, int size, int start, int *buf, int level,
                bool *used, int **sets, int *sizes, int *count)
{
    int i;
    sets[*count] = malloc(level * sizeof(int));
    memcpy(sets[*count], buf, level * sizeof(int));
    sizes[*count] = level;
    (*count)++;
    for (i = start; i < size; i++) {
        if (!used[i]) {
            if (i > 0 && !used[i - 1] && nums[i - 1] == nums[i]) continue;
            used[i] = true;
            buf[level] = nums[i];
            dfs(nums, size, i + 1, buf, level + 1, used, sets, sizes, count);
            used[i] = false;
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
static int** subsets(int* nums, int numsSize, int** columnSizes, int* returnSize)
{
    qsort(nums, numsSize, sizeof(int), compare);
    int capacity = 5000;
    int **sets = malloc(capacity * sizeof(int *));
    int *buf = malloc(numsSize * sizeof(int));
    bool *used = malloc(numsSize);
    memset(used, false, numsSize);
    *columnSizes = malloc(capacity * sizeof(int));
    *returnSize = 0;
    dfs(nums, numsSize, 0, buf, 0, used, sets, *columnSizes, returnSize);
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
