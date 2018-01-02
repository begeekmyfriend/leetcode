#include <stdio.h>
#include <stdlib.h>

static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int findKthLargest(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    return nums[numsSize - k];
}


int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test k n1 n2...\n");
        exit(-1);
    }

    int i, count = argc - 2;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 2]);
    }
    printf("%d\n", findKthLargest(nums, count, atoi(argv[1])));
    return 0;
}
