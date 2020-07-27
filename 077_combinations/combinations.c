#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void dfs(int n, int k, int start, int *stack, int len,
                int **results, int *count, int *col_sizes)
{
    int i;
    if (len == k) {
        col_sizes[*count] = k;
        results[*count] = malloc(k * sizeof(int));
        memcpy(results[*count], stack, k * sizeof(int));
        (*count)++;
    } else {
        for (i = start; i <= n; i++) {
            stack[len] = i;
            dfs(n, k, i + 1, stack, len + 1, results, count, col_sizes);
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int capacity = 10000;
    int count = 0;
    int **results = malloc(capacity * sizeof(int *));
    int *stack = malloc(k * sizeof(int));
    *returnColumnSizes = malloc(capacity * sizeof(int));
    dfs(n, k, 1, stack, 0, results, &count, *returnColumnSizes);
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
    int **lists = combine(atoi(argv[1]), atoi(argv[2]), &count, &col_sizes);
    for (i = 0; i < count; i++) {
        for (j = 0; j < col_sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
