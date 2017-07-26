#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

static void insert_sort(int *a, int size)
{
    int i, j;
    for (i = 1; i < size; i++) {
        int tmp = a[i];
        for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

static int threeSumClosest(int* nums, int numsSize, int target) {
    int i, min_diff = INT_MAX;

    if (numsSize < 3) {
        return min_diff;
    }

    insert_sort(nums, numsSize);

    for (i = 0; i < numsSize - 2; i++) {
        int left = i + 1;
        int right = numsSize - 1;
        while (left < right) {
            int diff = nums[i] + nums[left] + nums[right] - target;
            if (abs(diff) < abs(min_diff)) {
                min_diff = diff;
            }
            if (diff < 0) {
                left++;
            } else if (diff > 0) {
                right--;
            } else {
                break;
            }
        }
    }
    return min_diff + target;
}

int main(void)
{
    int i, target = 1;
    int nums[] = { -1, 2, 1, -4 };
    printf("%d\n", threeSumClosest(nums, sizeof(nums) / sizeof(nums[0]), target));
    return 0;
}
