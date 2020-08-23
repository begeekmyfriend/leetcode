#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int compare(const void *a, const void *b)
{
    return ((int *) a)[0] - ((int *) b)[0];
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes)
{
    if (intervalsSize == 0) {
        *returnSize = 0;
        return intervals;
    }
    
    int i, len = 0;
    int *tmp = malloc(intervalsSize * 2 * sizeof(int));
    for (i = 0; i < intervalsSize; i++) {
        tmp[i * 2] = intervals[i][0];
        tmp[i * 2 + 1] = intervals[i][1];
    }
    qsort(tmp, intervalsSize, 2 * sizeof(int), compare);

    intervals[0][0] = tmp[0];
    intervals[0][1] = tmp[1];
    for (i = 1; i < intervalsSize; i++) {
        if (tmp[i * 2] > intervals[len][1]) {
            len++;
            intervals[len][0] = tmp[i * 2];
            intervals[len][1] = tmp[i * 2 + 1];
        } else if (tmp[i * 2 + 1] > intervals[len][1]) {
            /* merge this interval */
            intervals[len][1] = tmp[i * 2 + 1];
        }
    }
    
    len += 1;
    *returnSize = len;
    *returnColumnSizes = malloc(len * sizeof(int));
    for (i = 0; i < len; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    
    return intervals;
}

int main(int argc, char **argv)
{
    if (argc < 1|| argc % 2 == 0) {
        fprintf(stderr, "Usage: ./test s0 e0 s1 e1...");
        exit(-1);
    }

    int i, count = 0;
    int *sizes = malloc((argc - 1) / 2 * sizeof(int));
    int **intervals = malloc((argc - 1) / 2 * sizeof(int *));
    for (i = 0; i < (argc - 1) / 2; i++) {
        sizes[i] = 2;
        intervals[i] = malloc(2 * sizeof(int));
        intervals[i][0] = atoi(argv[i * 2 + 1]);
        intervals[i][1] = atoi(argv[i * 2 + 2]);
    }

    int *col_sizes;
    int **results = merge(intervals, (argc - 1) / 2, sizes, &count, &col_sizes);
    for (i = 0; i < count; i++) {
        printf("[%d,%d]\n", results[i][0], results[i][1]);
    }

    return 0;
}
