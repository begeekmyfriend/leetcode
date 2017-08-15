#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse(int *a, int size)
{
    int left = 0;
    int right = size - 1;
    while (left < right) {
        int tmp = a[left];
        a[left] = a[right];
        a[right] = tmp;
        left++;
        right--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    if (numsSize <= 1) {
        return;
    }

    int *p = nums + numsSize - 1;    
    int *q = nums + numsSize - 1;

    while (p != nums && *(p - 1) >= *p) {
        p--;
    }

    if (p != nums) {
        int n = *(p - 1);
        while (*q <= n) {
            q--;
        }

        int tmp = *q;
        *q = *(p - 1);
        *(p - 1) = tmp;
    }
    reverse(p, numsSize - (p - nums));
}

static char* getPermutation(int n, int k) {
    int i;
    int *permutation = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        permutation[i] = i + 1;
    }
    while (--k > 0) {
        nextPermutation(permutation, n);
    }
    char *result = malloc(n + 1);
    for (i = 0; i < n; i++) {
        result[i] = permutation[i] + '0';
    }
    result[n] = '\0';
    free(permutation);
    return result;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./test n, k\n");
        exit(-1);
    }

    printf("%s\n", getPermutation(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
