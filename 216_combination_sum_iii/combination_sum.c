#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void dfs(int *nums, int size, int start, int target, int k,
                int *solution, int len, int **results, int *count, int *col_sizes)
{
    int i;
    if (len == k) {
        if (target == 0) {
            results[*count] = malloc(len * sizeof(int));
            memcpy(results[*count], solution, len * sizeof(int));
            col_sizes[*count] = len;
            (*count)++;
        }
    } else if (target > 0) {
        for (i = start; i < size; i++) {
            solution[len] = nums[i];
            dfs(nums, size, i + 1, target - nums[i], k, solution, len + 1, results, count, col_sizes);
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *returnColumnSizes array.
 ** Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 **/
static int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes)
{
    int i, count = 9;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = i + 1;
    }

    int *solution = malloc(k * sizeof(int));
    int **results = malloc(100 * sizeof(int *));
    *returnColumnSizes = malloc(100 * sizeof(int));
    *returnSize = 0;
    dfs(nums, count, 0, n, k, solution, 0, results, returnSize, *returnColumnSizes);
    return results;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test k n\n");
        exit(-1);
    }

    int i, j;
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    int *sizes, count = 0; 
    int **lists = combinationSum3(k, n, &count, &sizes);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
