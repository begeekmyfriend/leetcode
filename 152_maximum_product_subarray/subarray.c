#include <stdio.h>
#include <stdlib.h>

static int maxProduct(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return 0;
    }

    int i, global_max = nums[0], product;
    int local_min = 1, local_max = 1;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            product = local_max * nums[i];
            global_max = product > global_max ? product : global_max;
            local_max *= nums[i];
            local_min *= nums[i];
        } else if (nums[i] < 0) {
            product = local_min * nums[i];
            global_max = product > global_max ? product : global_max;
            int tmp = local_max;
            local_max = product > 1 ? product : 1;
            local_min = tmp * nums[i];
        } else {
            global_max = global_max > 0 ? global_max : 0;
            local_max = 1;
            local_min = 1;
        }
    }

    return global_max;
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", maxProduct(nums, count));
    return 0;
}
