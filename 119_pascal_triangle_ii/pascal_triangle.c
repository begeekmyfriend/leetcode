#include <stdio.h>
#include <stdlib.h>

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int* getRow(int rowIndex, int* returnSize)
{
    int *row = malloc((rowIndex + 1) * sizeof(int));
    *returnSize = rowIndex + 1;

    int num = rowIndex + 1;
    if (rowIndex < 1) {
        row[0] = 1;
        return row;
    }

    int i, j;
    for (i = 1; i <= rowIndex; i++) {
        num = i + 1;
        row[0] = 1;
        row[num - 1] = 1;
        for (j = num - 2; j >= 1; j--) {
            row[j] = row[j - 1] + row[j];
        }
    }

    return row;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }
    int i, j, count = 0, row_idx = atoi(argv[1]);
    int *row = getRow(row_idx, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", row[i]);
    }
    printf("\n");
    return 0;
}
