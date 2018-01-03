#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void dfs(int n, int k, int start, int *stack, int len,
                bool *used, int *col_sizes, int **results, int *count)
{
    int i;
    if (len == k) {
        col_sizes[*count] = k;
        results[*count] = malloc(k * sizeof(int));
        memcpy(results[*count], stack, k * sizeof(int));
        (*count)++;
    } else {
        for (i = start; i <= n; i++) {
            if (!used[i]) {
                stack[len] = i;
                used[i] = true;
                dfs(n, k, i + 1, stack, len + 1, used, col_sizes, results, count);
                used[i] = false;
            }
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int** columnSizes, int* returnSize) {
    int capacity = 10000;
    int count = 0;
    int **results = malloc(capacity * sizeof(int *));
    int *stack = malloc(k * sizeof(int));
    bool *used = malloc((n + 1) * sizeof(bool));
    memset(used, false, n + 1);
    *columnSizes = malloc(capacity * sizeof(int));
    dfs(n, k, 1, stack, 0, used, *columnSizes, results, &count);
    *returnSize = count;
    return results;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test n k\n");
        exit(-1);
    }

    int i, j, *col_sizes, count = 0;
    int **lists = combine(atoi(argv[1]), atoi(argv[2]), &col_sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < col_sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
