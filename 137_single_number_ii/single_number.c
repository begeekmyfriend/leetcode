#include <stdio.h>
#include <stdlib.h>

#if 0
static void singleNumber(int *nums, int numsSize)
{
    int i, xor = 0;
    for (i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }

    int mask = 1;
    while (!(mask & xor)) {
        mask <<= 1;
    }

    int zero = 0;
    int one = 0;
    for (i = 0; i < numsSize; i++) {
        if (nums[i] & mask) {
            one ^= nums[i];
        } else {
            zero ^= nums[i];
        }
    }

    printf("%d %d\n", zero, one);
}
#endif

static int singleNumber(int *nums, int numsSize)
{
#if 1
    int i, j, count[32], mask = 0;
    for (i = 0; i < 32; i++) {
        count[i] = 0;
        for (j = 0; j < numsSize; j++) {
            if ((1 << i) & nums[j]) {
                count[i]++;
            }
        }
        mask |= (count[i] % 3) << i;
    }
    return mask;
#else
    int i, ones = 0, twos = 0, threes = 0;
    for (i = 0; i < numsSize; i++) {
        /* `ones & nums[i]` the result is the bitmask which the bits appeared twice */
        twos |= ones & nums[i]; 
        /* reset mask twice in `ones` */
        ones ^= nums[i];
        /* count the `three` */
        threes = ones & twos;
        /* clear the `ones` and `twos` if the i-th bit had appeared three times. */
        ones &= ~threes;
        twos &= ~threes;
    }
    return ones;
#endif
}

int main(int argc, char **argv)
{
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", singleNumber(nums, count));
    return 0;
}
