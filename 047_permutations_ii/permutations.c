#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void dfs(int *nums, int size, int *stack, int len,
                bool *used, int **results, int *count)
{
    int i;
    if (len == size) {
        results[*count] = malloc(len * sizeof(int));
        memcpy(results[*count], stack, len * sizeof(int));
        (*count)++;
    } else {
        for (i = 0; i < size; i++) {
            if (!used[i]) {
                if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
                used[i] = true;
                stack[len] = nums[i];
                dfs(nums, size, stack, len + 1, used, results, count);
                used[i] = false;
            }
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int **permute(int* nums, int numsSize, int* returnSize)
{
    qsort(nums, numsSize, sizeof(int), compare);

    int count = 0, cap = 10000;
    int *stack = malloc(numsSize * sizeof(int));
    int **results = malloc(cap * sizeof(int *));
    bool *used = malloc(numsSize);
    memset(used, false, numsSize);
    *returnSize = 0;
    dfs(nums, numsSize, stack, 0, used, results, returnSize);
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
        printf("%d\n", nums[i]);
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
