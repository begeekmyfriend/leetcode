#include <stdio.h>
#include <stdlib.h>

/**
 ** Return an array of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
int* grayCode(int n, int* returnSize) {
    if (n < 0) {
        return NULL;
    }

    int i, count = 1 << n;
    int *codes = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        codes[i] = (i >> 1) ^ i;
    }

    *returnSize = 1 << n;
    return codes;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test n\n");
        exit(-1);
    }

    int i, count;
    int *list = grayCode(atoi(argv[1]), &count);
    for (i = 0; i < count; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}
