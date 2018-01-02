#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void dfs(int *nums, int size, int start, int **results, int *count)
{
    int i;
    if (start == size) {
        results[*count] = malloc(size * sizeof(int));
        memcpy(results[*count], nums, size * sizeof(int));
        (*count)++;
    } else {
        for (i = start; i < size; i++) {
            swap(nums + start, nums + i);
            dfs(nums, size, start + 1, results, count);
            swap(nums + start, nums + i);
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int **permute(int* nums, int numsSize, int* returnSize)
{
    int count = 0, cap = 5000;
    int **results = malloc(cap * sizeof(int *));
    *returnSize = 0;
    dfs(nums, numsSize, 0, results, returnSize);
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

    int **lists = permute(nums, argc - 1, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < argc - 1; j++) {
            printf("%d", lists[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
