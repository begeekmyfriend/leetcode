#include <stdio.h>
#include <stdlib.h>

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

static void nextPermutation(int* nums, int numsSize)
{
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

int main(int argc, char **argv)
{
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./test ...\n");
        exit(-1);
    }

    int i;
    int *nums = malloc(sizeof(int));
    for (i = 0; i < argc - 1; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    nextPermutation(nums, argc - 1);

    for (i = 0; i < argc - 1; i++) {
        printf("%d", nums[i]);
    }
    putchar('\n');

    return 0;
}
