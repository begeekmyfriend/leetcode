#include <stdio.h>
#include <stdlib.h>


static int partition(int *nums, int lo, int hi)
{
    if (lo >= hi) {
        return hi;
    }

    int i = lo;
    int j = hi;
    int pivot = nums[hi];
    while (i < j) {
        while (i < j && nums[i] <= pivot) { i++; }
        /* Loop invariant: nums[i] > pivot or i == j */
        nums[j] = nums[i];
        while (i < j && nums[j] >= pivot) { j--; }
        /* Loop invariant: nums[j] > pivot or i == j */
        nums[i] = nums[j];
    }
    /* Loop invariant: i == j */
    nums[i] = pivot;
    return i;
}

int findKthLargest(int* nums, int numsSize, int k)
{
    int lo = 0, hi = numsSize - 1;
    for (; ;) {
        printf("A:%d %d\n", lo, hi);
        int p = partition(nums, lo, hi);
        printf("B:%d %d\n", p, numsSize - k);
        if (p < numsSize - k) {
            lo = p + 1;
        } else if (p > numsSize - k) {
            hi = p - 1;
        } else {
            lo = p;
            break;
        }
    }
    return nums[lo];
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
