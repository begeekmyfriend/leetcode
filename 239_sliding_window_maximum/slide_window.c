#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    int i, head = 0, tail = 0;
    int count = 0;
    int *indexes = malloc(numsSize * sizeof(int));
    int *results = malloc((numsSize - k + 1) * sizeof(int));

    for (i = 0; i < numsSize; i++) {
        /* monotonous decreasing */
        while (tail > head && nums[i] >= nums[indexes[tail - 1]]) {
            tail--;
        }
        indexes[tail++] = i;

        if (indexes[head] <= i - k) {
            head++;
        }

        if (i >= k - 1) {
            results[count++] = nums[indexes[head]];
        }
    }

    *returnSize = count;
    return results;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test k n1 n2...\n");
        exit(-1);
    }

    int i, size = argc - 2;
    int k = atoi(argv[1]);
    int *nums = malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        nums[i] = atoi(argv[i + 2]);
    }

    int count = 0;
    int *lists = maxSlidingWindow(nums, size, k, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", lists[i]); 
    }
    printf("\n");
    return 0;
}
