#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *cache1, *cache2;

static void insert_sort(int *nums, int size)
{
    int i, j;
    for (i = 1; i < size; i++) {
        int tmp = nums[i];
        for (j = i - 1; j >= 0 && tmp < nums[j]; j--) {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = tmp;
    }
}

static int exist(int **results, int count, int *sizes, int *buf, int len)
{
    int i, j;
    for (i = 0; i < count; i++) {
        if (len == sizes[i]) {
            memcpy(cache1, results[i], len * sizeof(int));
            memcpy(cache2, buf, len * sizeof(int));
            insert_sort(cache1, len);
            insert_sort(cache2, len);
            if (!memcmp(cache1, cache2, len * sizeof(int))) {
                return 1;
            }
        }
    }
    return 0;
}

static void subset_recursive(int *nums, int size, int start,
                             int *buf, int len,
                             int **sets, int *sizes, int *count)
{
    int i;
    if (!exist(sets, *count, sizes, buf, len)) {
        sets[*count] = malloc(len * sizeof(int));
        memcpy(sets[*count], buf, len * sizeof(int));
        sizes[*count] = len;
        (*count)++;
    }
    for (i = start; i < size; i++) {
        buf[len++] = nums[i];
        subset_recursive(nums, size, i + 1, buf, len, sets, sizes, count);
        len--;
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** The sizes of the arrays are returned as *columnSizes array.
 ** Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 **/
int** subsets(int* nums, int numsSize, int** columnSizes, int* returnSize) {
    int capacity = 5000;
    int **sets = malloc(capacity * sizeof(int *));
    int *buf = malloc(numsSize * sizeof(int));
    *columnSizes = malloc(capacity * sizeof(int));
    *returnSize = 0;
    cache1 = malloc(numsSize * sizeof(int));
    cache2 = malloc(numsSize * sizeof(int));
    subset_recursive(nums, numsSize, 0, buf, 0, sets, *columnSizes, returnSize);
    return sets;
}

int main(int argc, char **argv)
{
    int i, j;
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./test array...\n");
        exit(-1);
    }
    int size = argc - 1;
    int *nums = malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    int *sizes;
    int count;
    int **lists = subsets(nums, size, &sizes, &count);
    for (i = 0; i < count; i++) {
        for (j = 0; j < sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }
    return 0;
}
