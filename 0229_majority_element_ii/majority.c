#include <stdio.h>
#include <stdlib.h>

static int *majorityElement(int* nums, int numsSize, int *returnSize)
{
    int i, m = -1, n = -1, cm = 0, cn = 0;
    for (i = 0; i < numsSize; i++) {
        if (m == nums[i]) {
            cm++;
        } else if (n == nums[i]) {
            cn++;
        } else if (cm == 0) {
            m = nums[i];
            cm++;
        } else if (cn == 0) {
            n = nums[i];
            cn++;
        } else {
            cm--;
            cn--;
        }
    }

    cm = 0;
    cn = 0;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] == m) {
            cm++;
        } else if (nums[i] == n) {
            cn++;
        }
    }

    int count = 0;
    int *results = malloc(2 * sizeof(int));
    if (cm > numsSize / 3) {
        results[count++] = m;
    }
    if (cn > numsSize / 3) {
        results[count++] = n;
    }

    *returnSize = count;
    return results;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test target n1 n2...\n");
        exit(-1);
    }

    int i, size = argc - 1;
    int *nums = malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    int count = 0;
    int *results = majorityElement(nums, size, &count);
    for (i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");
    return 0;
}
