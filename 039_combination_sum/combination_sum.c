#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            /* You may dump the content of the solution here, and you would find
             * the order of element represents the number of nested layers, and
             * the element at the specific order represents the iteration from
             * the start in the current recursive layer.
             */
            solution[len++] = nums[i];
            combination_recursive(nums, size, i, target - nums[i], solution, len, results, column_sizes, count);
            len--;
        }
    } else if (target == 0) {
        results[*count] = malloc(len * sizeof(int));
        memcpy(results[*count], solution, len * sizeof(int));
        column_sizes[*count] = len;
        (*count)++;
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
int** combinationSum(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize) {
    insert_sort(candidates, candidatesSize);

    int *solution = malloc(target * sizeof(int));
    int **results = malloc(100 * sizeof(int *));
    *columnSizes = malloc(100 * sizeof(int));
    *returnSize = 0;
    combination_recursive(candidates, candidatesSize, 0, target, solution, 0, results, *columnSizes, returnSize);
    return results;
    //for (i = 0; i < candidatesSize; i++) {
    //    //int *columns = malloc();
    //    for (j = 1; candidates[i] * j < target, j++) {
    //        for (k = i + 1; k < candidatesSize; k++) {
    //            
    //        }
    //        int remain = target - candidates[i] * j;
    //        if (remain == 0) {
    //            int *column = malloc(sizeof(int));
    //            if (count + 1 >= cap) {
    //                cap *= 2;
    //                columnSizes = realloc(columnSizes, cap * sizeof(int *));
    //            }
    //            columnSizes[count++] = column;
    //        } else {
    //            k = i + 1;
    //        }
    //    }
    //}
}

int main(int argc, char **argv)
{
    if (argc <= 2) {
        fprintf(stderr, "Usage: ./test target array...\n");
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
