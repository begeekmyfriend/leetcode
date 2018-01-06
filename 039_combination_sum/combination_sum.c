#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dfs(int *nums, int size, int start, int target, int *stack,
                int len, int **results, int *column_sizes, int *count)
{
    int i;
    if (target == 0) {
        results[*count] = malloc(len * sizeof(int));
        memcpy(results[*count], stack, len * sizeof(int));
        column_sizes[*count] = len;
        (*count)++;
    } else if (target > 0) {
        for (i = start; i < size; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            stack[len] = nums[i];
            dfs(nums, size, i, target - nums[i], stack, len + 1, results, column_sizes, count);
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
static int** combinationSum(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize)
{
    int cap = 100;
    int *stack = malloc(target * sizeof(int));
    int **results = malloc(cap * sizeof(int *));
    *columnSizes = malloc(cap * sizeof(int));
    *returnSize = 0;
    dfs(candidates, candidatesSize, 0, target, stack, 0, results, *columnSizes, returnSize);
    return results;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test target n1 n2...\n");
        exit(-1);
    }

    int i, j, count = 0;
    int target = atoi(argv[1]);
    int *nums = malloc((argc - 2) * sizeof(int));
    for (i = 0; i < argc - 2; i++) {
        nums[i] = atoi(argv[i + 2]);
    }

    int *sizes;
    int **lists = combinationSum(nums, argc - 2, target, &sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
