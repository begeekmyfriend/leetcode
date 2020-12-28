#include <stdio.h>
#include <stdlib.h>


static int compare(const void *a, const void *b)
{
    return ((int *) a)[0] - ((int *) b)[0];
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes)
{
    int i, len = 0;
    int *tmp = malloc((intervalsSize + 1) * 2 * sizeof(int));
    for (i = 0; i < intervalsSize; i++) {
        tmp[i * 2] = intervals[i][0];
        tmp[i * 2 + 1] = intervals[i][1];
    }
    tmp[i * 2] = newInterval[0];
    tmp[i * 2 + 1] = newInterval[1];
    qsort(tmp, intervalsSize + 1, 2 * sizeof(int), compare);

    int **results = malloc((intervalsSize + 1) * sizeof(int *));
    results[0] = malloc(2 * sizeof(int));
    results[0][0] = tmp[0];
    results[0][1] = tmp[1];
    for (i = 1; i < intervalsSize + 1; i++) {
        results[i] = malloc(2 * sizeof(int));
        if (tmp[i * 2] > results[len][1]) {
            len++;
            results[len][0] = tmp[i * 2];
            results[len][1] = tmp[i * 2 + 1];
        } else if (tmp[i * 2 + 1] > results[len][1]) {
            /* merge this interval */
            results[len][1] = tmp[i * 2 + 1];
        }
    }
    
    len += 1;
    *returnSize = len;
    *returnColumnSizes = malloc(len * sizeof(int));
    for (i = 0; i < len; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    
    return results;
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc % 2 == 0) {
        fprintf(stderr, "Usage: ./test new_s new_e s0 e0 s1 e1...");
        exit(-1);
    }

    int new_interv[2];
    new_interv[0] = atoi(argv[1]);
    new_interv[1] = atoi(argv[2]);

    int i, count = 0;
    int *size = malloc((argc - 3) / 2 * sizeof(int));
    int **intervals = malloc((argc - 3) / 2 * sizeof(int *));
    for (i = 0; i < (argc - 3) / 2; i++) {
        intervals[i] = malloc(2 * sizeof(int));
        intervals[i][0] = atoi(argv[i * 2 + 3]);
        intervals[i][1] = atoi(argv[i * 2 + 4]);
    }

    int *col_sizes;
    int **results = insert(intervals, (argc - 3) / 2, size, new_interv, 2, &count, &col_sizes);
    for (i = 0; i < count; i++) {
        printf("[%d,%d]\n", results[i][0], results[i][1]);
    }

    return 0;
}
