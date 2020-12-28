#include <stdio.h>
#include <stdlib.h>

static int majorityElement(int* nums, int numsSize)
{
    int i, major, count = 0;
    for (i = 0; i < numsSize; i++) {
        if (count == 0) {
            major = nums[i];
            count++;
        } else if (major == nums[i]) {
            count++;
        } else {
            count--;
        }
    }
    return major;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test target n1 n2...\n");
        exit(-1);
    }

    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    printf("%d\n", majorityElement(nums, count));
    return 0;
}
