#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void dfs(int *nums, int size, bool *used, int *stack,
                int len, int **results, int *count, int *col_size)
{
    int i;
    if (len == size) {
        results[*count] = malloc(len * sizeof(int));
        memcpy(results[*count], stack, len * sizeof(int));
        col_size[*count] = size;
        (*count)++;
    } else {
        /* Reverse order is allowed in different levels, always starts from [0] */
        for (i = 0; i < size; i++) {
            /* Used marks only allows remaining elements in DFS levels */
            if (!used[i]) {
                if (i > 0 && !used[i - 1] && nums[i - 1] == nums[i]) {
                    /* In case that duplicate permutation with same elemements but in different postions */
                    continue;
                }
                used[i] = true;
                stack[len] = nums[i];
                dfs(nums, size, used, stack, len + 1, results, count, col_size);
                used[i] = false;
            }
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 */
static int **permute(int* nums, int numsSize, int* returnSize, int **returnColumnSize)
{
    qsort(nums, numsSize, sizeof(int), compare);

    int count = 0, cap = 10000;
    int *stack = malloc(numsSize * sizeof(int));
    int **results = malloc(cap * sizeof(int *));
    bool *used = malloc(numsSize * sizeof(bool));
    memset(used, false, numsSize * sizeof(bool));
    *returnSize = 0;
    *returnColumnSize = malloc(cap * sizeof(int));
    dfs(nums, numsSize, used, stack, 0, results, returnSize, *returnColumnSize);
    return results;
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./test ...\n");
        exit(-1);
    }

    int i, j, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    int *size;
    int **lists = permute(nums, argc - 1, &count, &size);
    for (i = 0; i < count; i++) {
        for (j = 0; j < argc - 1; j++) {
            printf("%d", lists[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
