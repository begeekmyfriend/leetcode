#include <stdio.h>
#include <stdlib.h>


static void merge(int* nums1, int m, int* nums2, int n)
{
    int i = m - 1, j = n - 1, k = nums1Size - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] >= nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }

    while (j >= 0) {
        nums1[k--] = nums2[j--];
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
