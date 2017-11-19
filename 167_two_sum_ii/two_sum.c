#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
static int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    int i = 0, j = numbersSize - 1;
    while (i < j) {
        int diff = target - numbers[i];
        if (diff < numbers[j]) {
            while (i < --j && numbers[j + 1] == numbers[j]) {}
        } else if (diff > numbers[j]) {
            while (++i < j && numbers[i - 1] == numbers[i]) {}
        } else {
            *returnSize = 2;
            int *indexes = malloc(*returnSize * sizeof(int));
            indexes[0] = i + 1;
            indexes[1] = j + 1;
            return indexes;
        }
    }

    *returnSize = 0;
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test target n1 n2...");
        exit(-1);
    }

    int i, count = argc - 2;
    int target = atoi(argv[1]);
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 2]);
    }

    int number = 0;
    int *indexes = twoSum(nums, count, target, &number);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    }
    return 0;
}
