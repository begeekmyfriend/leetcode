#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static int minSubArrayLen(int s, int* nums, int numsSize)
{
    int i, sum = 0, len = INT_MAX, start = 0;
    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
        while (sum >= s) {
            /* sliding window */
            len = min(len, i - start + 1);
            sum -= nums[start++];
        }
    }

    return len == INT_MAX ? 0 : len;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test sum n1 n2...\n");
        exit(-1);
    }

    int i, count = argc - 2;
    int sum = atoi(argv[1]);
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 2]);
    }
    printf("%d\n", minSubArrayLen(sum, nums, count));
    return 0;
}
