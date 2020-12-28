#include <stdio.h>
#include <stdlib.h>


static int search(int* nums, int numsSize, int target)
{
    int lo = 0;
    int hi = numsSize - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[hi]) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    int i;
    int target = atoi(argv[1]);
    int size = argc - 2;
    int *nums = malloc(size * sizeof(int));

    for (i = 0; i < argc - 2; i++) {
        nums[i] = atoi(argv[i + 2]);
    }
    printf("%d\n", search(nums, size, target));
    return 0;
}
