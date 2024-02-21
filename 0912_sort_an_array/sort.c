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

static void merge(int *nums, int lo, int mid, int hi)
{
    int i, j, k, size = hi - mid;
    int *tmp = malloc(size * sizeof(int));

    for (j = 0; j < size; j++) {
        tmp[j] = nums[mid + 1 + j];
    }

    i = mid;
    j = size - 1;
    k = hi;
    while (i >= lo && j >= 0) {
        if (tmp[j] >= nums[i]) {
            nums[k--] = tmp[j--];
        } else {
            nums[k--] = nums[i--];
        }
    }

    while (j >= 0) {
        nums[k--] = tmp[j--];
    }

    free(tmp);
}

static void merge_sort(int *nums, int lo, int hi)
{
    int mid;

    if (lo >= hi) {
        return;
    }

    mid = lo + (hi - lo) / 2;

    merge_sort(nums, lo, mid);
    merge_sort(nums, mid + 1, hi);

    merge(nums, lo, mid, hi);
}

int *sortArray(int *nums, int numsSize, int *returnSize)
{
#if 1
    quick_sort(nums, 0, numsSize - 1);
#else
    merge_sort(nums, 0, numsSize - 1);
#endif
    *returnSize = numsSize;
    return nums;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int ret_size = 0;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    show(sortArray(nums, count, &ret_size), 0, ret_size - 1);

    return 0;
}
