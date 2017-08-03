#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool exist(int **results, int count, int *solution, int len)
{
    int i;
    for (i = 0; i < count; i++) {
        if (!memcmp(results[i], solution, len * sizeof(int))) {
            return true;
        }
    }
    return false;
}

static void insert_sort(int *a, int size)
{
    int i, j;
    for (i = 1; i < size; i++) {
        int tmp = a[i];
        for (j = i - 1; j >= 0 && tmp < a[j]; j--) {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

static void combination_recursive(int *nums, int size, int start, int target,
                                  int *solution, int len,
                                  int **results, int *column_sizes, int *count)
{
    int i;
    if (target > 0) {
        for (i = start; i < size; i++) {
            /* You may dump the content of the solution here, and you would find
             * the order of element represents the number of nested layers, and
             * the element at the specific order represents the iteration from
             * the start in the current recursive layer.
             */
            solution[len++] = nums[i];
            combination_recursive(nums, size, i + 1, target - nums[i], solution,
                                  len, results, column_sizes, count);
            len--;
        }
    } else if (target == 0) {
        if (!exist(results, *count, solution, len)) {
            results[*count] = malloc(len * sizeof(int));
            memcpy(results[*count], solution, len * sizeof(int));
            column_sizes[*count] = len;
            (*count)++;
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
    insert_sort(candidates, candidatesSize);

    int *solution = malloc(target * sizeof(int));
    int **results = malloc(100 * sizeof(int *));
    *columnSizes = malloc(100 * sizeof(int));
    *returnSize = 0;
    combination_recursive(candidates, candidatesSize, 0, target, solution, 0, results, *columnSizes, returnSize);
    return results;
}

int main(int argc, char **argv)
{
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
