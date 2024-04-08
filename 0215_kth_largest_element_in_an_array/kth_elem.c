#include <stdio.h>
#include <stdlib.h>


static void show(int *nums, int lo, int hi)
{
    int i;
    for (i = lo; i <= hi; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

static inline void swap(int *a, int *b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

static void max_heapify(int *nums, int size, int parent)
{
    int i = parent;  /* parent is the root */
    int l = parent * 2 + 1;
    int r = parent * 2 + 2;

    if (l < size && nums[l] > nums[i]) {
        i = l;
    }

    if (r < size && nums[r] > nums[i]) {
        i = r;
    }

    /* percolate up */
    if (i != parent) {
        swap(&nums[i], &nums[parent]);
        max_heapify(nums, size, i);
    }
}

static void build_max_heap(int *nums, int size)
{
    int i;
    for (i = size / 2; i >= 0; i--) {
        max_heapify(nums, size, i);
    }
}

static void quick_select(int *nums, int lo, int hi, int k)
{
    if (lo >= hi) {
        return;
    }

    int i = lo - 1;
    int j = hi;
    int pivot = nums[hi];

    while (i < j) {
        /* For case of large amounts of consecutive duplicate elements, we
         * shall make the partition in the middle of the array as far as
         * possible. If the partition is located in the head or tail, the
         * performance might well be very bad for it.
         */
        while (i < hi && nums[++i] > pivot) {}
        while (j > lo && nums[--j] < pivot) {}
        if (i < j) {
            swap(&nums[i], &nums[j]);
        }
    }

    /* invariant: i == j + 1 or i == j */
    swap(&nums[i], &nums[hi]);
    if (i + 1 >= k) {
        quick_select(nums, lo, i - 1, k);
    } else {
        quick_select(nums, i + 1, hi, k);
    }
}

int findKthLargest(int* nums, int numsSize, int k)
{
#if 1
    quick_select(nums, 0, numsSize - 1, k);
    return nums[k - 1];
#else
    int i;

    build_max_heap(nums, numsSize);

    /* nums[0] is the largest element and the last is the least */
    for (i = numsSize - 1; i >= numsSize - k + 1; i--) {
        swap(&nums[0], &nums[i]);
        max_heapify(nums, numsSize, 0);
    }

    return nums[0];
#endif
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
