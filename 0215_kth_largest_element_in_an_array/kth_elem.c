#include <stdio.h>
#include <stdlib.h>

static inline void swap(int *a, int *b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

static int quick_select(int *nums, int lo, int hi, int k)
{
    if (lo >= hi) {
        return hi;
    }

    int i = lo - 1;
    int j = hi + 1;
    int pivot = nums[lo];
    while (i < j) {
        /* For case of large amounts of consecutive duplicate elements, we
         * shall make the partition in the middle of the array as far as
         * possible. If the partition is located in the head or tail, the
         * performance might well be very bad for it.
         */
        while (nums[++i] > pivot) {}
        while (nums[--j] < pivot) {}
        if (i < j) {
            swap(&nums[i], &nums[j]);
        }
    }

    /* invariant: i == j + 1 or i == j */
    if (j >= k - 1) {
        return quick_select(nums, lo, j, k);
    } else {
        return quick_select(nums, j + 1, hi, k);
    }
}

int findKthLargest(int* nums, int numsSize, int k)
{
    int i = quick_select(nums, 0, numsSize - 1, k);
    return nums[i];
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
