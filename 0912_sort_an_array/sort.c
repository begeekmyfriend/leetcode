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

static void quick_sort(int *nums, int lo, int hi)
{
    int i, j, mid, pivot;

    if (lo >= hi) {
        return;
    }

    /* shuffle the pivot */
    mid = lo + (hi - lo) / 2;
    swap(&nums[mid], &nums[hi]);

    i = lo - 1;
    j = hi;
    pivot = nums[hi];
    while (i < j) {
        /* For case of large amounts of consecutive duplicate elements, we
         * shall make the partition in the middle of the array as far as
         * possible. If the partition is located in the head or tail, the
         * performance might well be very bad for it.
         */
        while (i < hi && nums[++i] < pivot) {}
        while (j > lo && nums[--j] > pivot) {}
        if (i < j) {
        swap(&nums[i], &nums[j]);
        }
    }

    /* Loop invariant: i == j + 1 or i == j */
    swap(&nums[i], &nums[hi]);
    quick_sort(nums, lo, i - 1);
    quick_sort(nums, i + 1, hi);
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    quick_sort(nums, 0, count - 1);
    show(nums, 0, count - 1);

    return 0;
}
