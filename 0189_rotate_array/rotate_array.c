#include <stdio.h>
#include <stdlib.h>

static void reverse(int *nums, int lo, int hi)
{
    while (lo < hi) {
        int tmp = nums[lo];
        nums[lo] = nums[hi];
        nums[hi] = tmp;
        lo++;
        hi--;
    }
}

static void rotate(int* nums, int numsSize, int k)
{
    k %= numsSize;
    if (k == 0) {
        return;
    }

    reverse(nums, 0, numsSize - 1 - k);
    reverse(nums, numsSize - k, numsSize - 1);
    reverse(nums, 0, numsSize - 1);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test k n1 n2...\n");
        exit(-1);
    }

    int k = atoi(argv[1]);
    int i, count = argc - 2;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 2]);
    }

    rotate(nums, count, k);

    for (i = 0; i < count; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
