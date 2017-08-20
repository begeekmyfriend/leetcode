#include <stdio.h>
#include <stdlib.h>

static int binary_search(int *nums, int len, int target)
{
    int low = -1;
    int high = len;
    while (low + 1 < high) {
        int mid = high - (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (high == len || nums[high] != target) {
        return -high - 1;
    } else {
        return high;
    }
}

static void merge(int* nums1, int m, int* nums2, int n)
{
    int i, j, len1 = m;
    for (i = 0; i < n; i++) {
        int index = binary_search(nums1, len1, nums2[i]);
        if (index < 0) {
            index = -index - 1;
        }
        for (j = len1 - 1; j >= index; j--) {
            nums1[j + 1] = nums1[j];
        }
        nums1[index] = nums2[i];
        len1++;
    }
}

int main(int argc, char **argv)
{
    int i;
    int nums1[] = { 1, 3, 5, 7, 9, 0, 0, 0, 0, 0 };
    int nums2[] = { 2, 4, 6, 8, 10 };
    int size1 = 5;//sizeof(nums1) / sizeof(*nums1);
    int size2 = sizeof(nums2) / sizeof(*nums2);
    merge(nums1, size1, nums2, size2);
    for (i = 0; i < sizeof(nums1) / sizeof(*nums1); i++) {
        printf("%d ", nums1[i]);
    }
    printf("\n");
    return 0;
}
