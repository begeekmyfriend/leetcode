#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void dfs(int *nums, int size, int start, int target, int *solution,
                int len, int **results, int *count, int *column_sizes)
{
    int i;
    if (target < 0) {
        return;
    } else if (target == 0) {
        results[*count] = malloc(len * sizeof(int));
        memcpy(results[*count], solution, len * sizeof(int));
        column_sizes[*count] = len;
        (*count)++;
    } else {
        int last = INT_MIN;
        for (i = start; i < size; i++) {
            if (last != nums[i]) {
                /* No duplicate combinations in different order */
                solution[len] = nums[i];
                /* i + 1 limits the candidate range in next levels */
                dfs(nums, size, i + 1, target - nums[i], solution, len + 1, results, count, column_sizes);
            }
            last = nums[i];
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *returnColumnSizes array.
 ** Note: Both returned array and *returnColumnSizes array must be malloced, assume caller calls free().
 **/
static int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes)
{
    qsort(candidates, candidatesSize, sizeof(int), compare);

    int *solution = malloc(target * sizeof(int));
    int **results = malloc(100 * sizeof(int *));
    *returnColumnSizes = malloc(100 * sizeof(int));
    *returnSize = 0;
    dfs(candidates, candidatesSize, 0, target, solution, 0, results, returnSize, *returnColumnSizes);
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
    int **lists = combinationSum(nums, argc - 2, target, &count, &sizes);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
