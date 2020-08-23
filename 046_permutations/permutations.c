#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if 0
static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void dfs(int *nums, int size, int start,
                int **results, int *count, int *col_size)
{
    int i;
    if (start == size) {
        results[*count] = malloc(size * sizeof(int));
        memcpy(results[*count], nums, size * sizeof(int));
        col_size[*count] = size;
        (*count)++;
    } else {
        for (i = start; i < size; i++) {
            /* A swap can make a new permutation but not be listed in order */
            swap(nums + start, nums + i);
            dfs(nums, size, start + 1, results, count, col_size);
            /* restore the array in backtrace */
            swap(nums + start, nums + i);
        }
    }
}
#endif

static void dfs(int *nums, int size, bool *used, int *stack,
                int len, int **results, int *count, int *col_size)
{
    int i;
    if (len == size) {
        results[*count] = malloc(size * sizeof(int));
        memcpy(results[*count], stack, size * sizeof(int));
        col_size[*count] = size;
        (*count)++;
    } else {
        /* Reverse order is allowed in different levels, always starts from [0] */
        for (i = 0; i < size; i++) {
            if (!used[i]) {
                /* Used marks only allows remaining elements in DFS levels */
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
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
static int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    int count = 0, cap = 5000;
    int **results = malloc(cap * sizeof(int *));
    bool *used = malloc(numsSize * sizeof(bool));
    int *stack = malloc(numsSize * sizeof(int));
    *returnSize = 0;
    *returnColumnSizes = malloc(cap * sizeof(int));
    memset(used, false, numsSize * sizeof(bool));
    dfs(nums, numsSize, used, stack, 0, results, returnSize, *returnColumnSizes);
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
