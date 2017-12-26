#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int minSubArrayLen(int s, int* nums, int numsSize)
{
    int i, j, sum = 0, min = INT_MAX;
    for (i = 0, j = 0; i < numsSize; i++) {
        sum += nums[i];
        if (sum >= s) {
            while (j <= i) {
                sum -= nums[j++];
                if (sum < s) {
                    int interv = i - j + 2;
                    min = interv < min ? interv : min;
                    if (min == 1) {
                        return 1;
                    }
                    break;
                }
            }
        }
    }

    return min == INT_MAX ? 0 : min;
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
